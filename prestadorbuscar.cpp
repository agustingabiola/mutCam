#include "prestadorbuscar.h"
#include "ui_prestadorbuscar.h"

#include <QKeyEvent>

PrestadorBuscar::PrestadorBuscar(QWidget *parent)
                            :QDialog(parent)
                            ,ui(new Ui::PrestadorBuscar){
    ui->setupUi(this);
    idPrestador=INVALIDO;
    setTableView();
    QTimer::singleShot(0, ui->lineEditBuscar, SLOT(setFocus()));
}

PrestadorBuscar::~PrestadorBuscar(){
    delete ui;
}

void PrestadorBuscar::setTableView(){
    QString busqueda="WHERE activado=1";
    BD::buscarPrestador(busqueda);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    model->setHeaderData(2, Qt::Horizontal, tr("RAZON SOCIAL"));
    model->setHeaderData(4, Qt::Horizontal, tr("E-M@IL"));
    QString styleSheet =  "QHeaderView::section {"
                         "spacing: 10px;"
                         "background-color: lightblue;"
                         "color: black;"
                         "border: 1px solid black;"
                         "margin: 1px;"
                         "text-align: right;"
                         "font-family: arialblack;"
                         "font-size: 20px; "
                         "height: 30px; }";
    ui->tableView->horizontalHeader()->setStyleSheet(styleSheet);
    styleSheet = "QTableView::item:selected{ background-color: lightblue; color: black;} ";
    ui->tableView->setStyleSheet(styleSheet);
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_pushButtonSeleccionar_clicked()));
    ui->tableView->setVisible(false);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setVisible(true);
}

void PrestadorBuscar::on_lineEditBuscar_textChanged(const QString &arg1){
    ui->lineEditBuscar->setText(arg1.toUpper());
    QStringList sl = arg1.toUpper().simplified().split(" ");
    QString busquedaRazonSocial = sl.join("%' AND UPPER (razon_social) LIKE '%");
    busquedaRazonSocial.prepend("WHERE ( UPPER (razon_social) LIKE '%");
    busquedaRazonSocial.append("%' ");
    QString busquedaCuit = sl.join("%' AND UPPER (cuit) LIKE '%");
    busquedaCuit.prepend(" OR  (cuit) LIKE '%");
    busquedaCuit.append("%'  ");
    QString busquedaDireccion = sl.join("%' AND UPPER (direccion) LIKE '%");
    busquedaDireccion.prepend(" OR  UPPER (direccion) LIKE '%");
    busquedaDireccion.append("%'  ");
    QString busquedaNombre = sl.join("%' AND UPPER (nombre) LIKE '%");
    busquedaNombre.prepend(" OR  UPPER (nombre) LIKE '%");
    busquedaNombre.append("%'  ");
    QString busqueda=busquedaRazonSocial+busquedaCuit+busquedaDireccion+busquedaNombre+") AND (activado=1) ";
    BD::buscarPrestador(busqueda);
    model->setHeaderData(2, Qt::Horizontal, tr("RAZON SOCIAL"));
    model->setHeaderData(4, Qt::Horizontal, tr("E-M@IL"));
    ui->tableView->setModel(model);
}

void PrestadorBuscar::on_pushButtonNuevoPrestador_clicked(){
    prestadorNuevo = new PrestadorNuevo();
    prestadorNuevo->exec();
    if (idPrestador!=INVALIDO)
        close();
    on_lineEditBuscar_textChanged(ui->lineEditBuscar->text());
}

void PrestadorBuscar::on_pushButtonSeleccionar_clicked(){
    int row=ui->tableView->selectionModel()->currentIndex().row();
    idPrestador=model->data(model->index(row,0), Qt::DisplayRole).toString();
    if (idPrestador!=INVALIDO){
        prestador.razon_social=model->data(model->index(row,2), Qt::DisplayRole).toString();
        prestador.nombre=model->data(model->index(row,1), Qt::DisplayRole).toString();
        prestador.telefono=model->data(model->index(row,3), Qt::DisplayRole).toString();
        prestador.mail=model->data(model->index(row,4), Qt::DisplayRole).toString();
        prestador.cuit=model->data(model->index(row,5), Qt::DisplayRole).toString();
        prestador.direccion=model->data(model->index(row,6), Qt::DisplayRole).toString();
        close();
    }
}

void PrestadorBuscar::on_pushButtonCancelar_clicked(){
    idPrestador=INVALIDO;
    close();
}

void PrestadorBuscar::on_pushButtonEliminar_clicked(){
    int row=ui->tableView->selectionModel()->currentIndex().row();
    idPrestador=model->data(model->index(row,0), Qt::DisplayRole).toString();
    if (idPrestador!=INVALIDO){
        prestador.razon_social=model->data(model->index(row,2), Qt::DisplayRole).toString();
        prestador.nombre=model->data(model->index(row,1), Qt::DisplayRole).toString();
        prestador.telefono=model->data(model->index(row,3), Qt::DisplayRole).toString();
        prestador.mail=model->data(model->index(row,4), Qt::DisplayRole).toString();
        prestador.cuit=model->data(model->index(row,5), Qt::DisplayRole).toString();
        prestador.direccion=model->data(model->index(row,6), Qt::DisplayRole).toString();
        QMessageBox::StandardButton reply;
        reply=QMessageBox::information(this, "Desea Continuar?"
                                  , "Si continua se borrara este PRESTADOR permanentemente. \n"
                                    "y ademas se borraran todos PAGOS / PRESTAMOS relacionadas con el mismo. \n"
                                    "En caso afirmativo se le pedira otra confirmacion"
                                  , QMessageBox::Ok|QMessageBox::No);
        if (reply==QMessageBox::Ok){
            reply=QMessageBox::critical(this, "Esta Seguro Que Desea Continuar?"
                                         , "Si continua borrara esta PRESTADOR permanentemente \n"
                                           "y ademas se borraran todos PAGOS / PRESTAMOS relacionadas con el mismo. \n"
                                           "Esta accion no se puede deshacer."
                                         , QMessageBox::Ok|QMessageBox::No);
            if (reply==QMessageBox::Ok){
                BD::eliminarPrestador();
            }
        }
    }
    on_lineEditBuscar_textChanged(ui->lineEditBuscar->text());
}

void PrestadorBuscar::keyPressEvent(QKeyEvent * event){
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
    QTimer::singleShot(0, ui->lineEditBuscar, SLOT(setFocus()));
}
