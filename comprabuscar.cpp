#include "comprabuscar.h"
#include "ui_comprabuscar.h"

#include <QKeyEvent>

CompraBuscar::CompraBuscar(QWidget *parent)
                            :QDialog(parent)
                            ,ui(new Ui::CompraBuscar){
    ui->setupUi(this);
    idCompra=INVALIDO;
    idPrestador=INVALIDO;
    idSocio=INVALIDO;
    ui->dateEditFinal->setDate(QDate::currentDate());
    ui->dateEditInicio->setDate(QDate::currentDate().addDays(-28));
    socioSeleccionado=false;
    prestadorSeleccionado=false;
    BD::buscarCompra("");
    ui->tableView->setModel(model);
    QString styleSheet =  "QHeaderView::section {"
                         "spacing: 10px;"
                         "background-color: lightblue;"
                         "color: black;"
                         "border: 1px solid black;"
                         "margin: 1px;"
                         "text-align: right;"
                         "font-family: arialblack;"
                         "height: 30px;"
                         "font-size: 20px; }";
    ui->tableView->horizontalHeader()->setStyleSheet(styleSheet);
    styleSheet = "QTableView::item:selected{ background-color: lightblue; color: black;} ";
    ui->tableView->setStyleSheet(styleSheet);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_pushButtonSeleccionar_clicked()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox()));
    connect(ui->dateEditInicio,SIGNAL(dateChanged(QDate)), this, SLOT(comboBox()));
    connect(ui->dateEditFinal,SIGNAL(dateChanged(QDate)), this, SLOT(comboBox()));
    connect(ui->radioButton,SIGNAL(toggled(bool)), this, SLOT(comboBox()));
    ui->tableView->setVisible(false);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setVisible(true);
    setTableView();
}

CompraBuscar::~CompraBuscar(){
    delete ui;
}

void CompraBuscar::setTableView(){
    QString finicio=ui->dateEditInicio->date().toString("dd-MM-yyyy");
    QString ffinal=ui->dateEditFinal->date().toString("dd-MM-yyyy");
    QString busquedaFecha="WHERE (compras.activado=1) "
            " AND ( "
            " ( (TO_DATE(fechamodificacion,'dd-MM-yy') >= TO_DATE( '"+finicio+"' ,'dd-MM-yyyy')) "
            " AND (TO_DATE( fechamodificacion,'dd-MM-yy') <= TO_DATE( '"+ffinal+"' ,'dd-MM-yyyy'))) "
            " OR ( (TO_DATE(fechaautorizacion,'dd-MM-yy') >= TO_DATE( '"+finicio+"' ,'dd-MM-yyyy'))  "
            " AND (TO_DATE( fechaautorizacion,'dd-MM-yy') <= TO_DATE( '"+ffinal+"' ,'dd-MM-yyyy'))) "
            " OR ( (TO_DATE(fechaautorizacion,'dd-MM-yy') <= TO_DATE( '"+finicio+"' ,'dd-MM-yyyy')) "
            " AND (TO_DATE( fechamodificacion,'dd-MM-yy') >= TO_DATE( '"+ffinal+"' ,'dd-MM-yyyy'))) "
            ")";
    QString busquedaTipo="";
    QString busquedaSocio="";
    QString busquedaPrestador="";
    QString busquedaTerminado="";
    if (ui->comboBox->currentIndex()!=0)
        busquedaTipo=" AND ( tipo='"+ui->comboBox->currentText()+"' )";
    if (socioSeleccionado)
        busquedaSocio=" AND ( compras.idsocio='"+idSocio+"' )";
    if (prestadorSeleccionado)
        busquedaPrestador=" AND ( compras.idprestador='"+idPrestador+"' )";
    if (ui->radioButton->isChecked()){
        busquedaTerminado=" AND (compras.terminado=0) ";
    }
    QString busqueda=busquedaFecha+busquedaTipo+busquedaSocio+busquedaPrestador+busquedaTerminado;
    BD::buscarCompra(busqueda);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(3);
    model->setHeaderData(1, Qt::Horizontal, tr("# SOCIO"));
    model->setHeaderData(2, Qt::Horizontal, tr("NOMBRE Y APELLIDO"));
    model->setHeaderData(4, Qt::Horizontal, tr("PRESTADOR"));
    model->setHeaderData(6, Qt::Horizontal, tr("CUOTAS"));
    model->setHeaderData(7, Qt::Horizontal, tr("ACTUAL"));
    model->setHeaderData(10, Qt::Horizontal, tr("AUTORIZADA"));
    model->setHeaderData(11, Qt::Horizontal, tr("MODIFICADA"));
}

void CompraBuscar::comboBox(){
    setTableView();
}

void CompraBuscar::on_pushButtonBuscarSocio_clicked(){
    searchSocio = new SocioBuscar();
    searchSocio->exec();
    if (idSocio!=INVALIDO)
        socioSeleccionado=true;
    showNormal();
    raise();
    activateWindow();
    ui->lineEditSocio->setText(socio.nombre+" "+socio.apellido);
    setTableView();
}

void CompraBuscar::on_pushButtonBuscarPrestador_clicked(){
    searchPrestador = new PrestadorBuscar();
    searchPrestador->exec();
    if (idPrestador!=INVALIDO)
        prestadorSeleccionado=true;
    showNormal();
    raise();
    activateWindow();
    ui->lineEditPrestador->setText(prestador.razon_social);
    setTableView();
}


void CompraBuscar::on_pushButtonSeleccionar_clicked(){
}

void CompraBuscar::on_pushButtonEliminar_clicked(){
    int row=ui->tableView->selectionModel()->currentIndex().row();
    idCompra=model->data(model->index(row,0), Qt::DisplayRole).toString();
    if (idCompra!=INVALIDO){
        idSocio=model->data(model->index(row,1), Qt::DisplayRole).toString();
        socio.nombre=model->data(model->index(row,2), Qt::DisplayRole).toString();
        prestador.nombre=model->data(model->index(row,4), Qt::DisplayRole).toString();
        compra.monto=model->data(model->index(row,5), Qt::DisplayRole).toString();
        compra.cantcuotas=model->data(model->index(row,6), Qt::DisplayRole).toString();
        QMessageBox::StandardButton reply;
        reply=QMessageBox::information(this, "Desea Continuar?"
                                  , "Si continua se borrara la COMPRA/PRESTAMO seleccionado PERMANENTEMENTE. \n"
                                    "#Socio: "+idSocio+", Socio: "+socio.nombre+" \n"
                                    "Prestador: "+prestador.nombre+" \n"
                                    "Monto: "+compra.monto+", Cuotas: "+compra.cantcuotas+" \n"
                                    "En caso afirmativo se le pedira otra confirmacion"
                                  , QMessageBox::Ok|QMessageBox::No);
        if (reply==QMessageBox::Ok){
            reply=QMessageBox::critical(this, "Esta Seguro Que Desea Continuar?"
                                        , "Si continua se borrara la COMPRA/PRESTAMO seleccionado PERMANENTEMENTE. \n"
                                          "#Socio: "+idSocio+", Socio: "+socio.nombre+" \n"
                                          "Prestador: "+prestador.nombre+" \n"
                                          "Monto: "+compra.monto+", Cuotas: "+compra.cantcuotas+" \n"
                                        , QMessageBox::Ok|QMessageBox::No);
            if (reply==QMessageBox::Ok){
                BD::eliminarCompra();
            }
        }
    }
    setTableView();
}

void CompraBuscar::on_pushButtonCancelar_clicked(){
    idPrestador=INVALIDO;
    idSocio=INVALIDO;
    idCompra=INVALIDO;
    close();
}

void CompraBuscar::keyPressEvent(QKeyEvent * event){
    switch (event->key()){
    case Qt::Key_Escape : close();
        break;
    case Qt::Key_Return : on_pushButtonSeleccionar_clicked();
        break;
    case Qt::Key_Up : ui->tableView->selectRow(ui->tableView->selectionModel()->currentIndex().row()-1);
        break;
    case Qt::Key_Down : ui->tableView->selectRow(ui->tableView->selectionModel()->currentIndex().row()+1);
        break;
    }
}
