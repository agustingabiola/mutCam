#include "sociobuscar.h"
#include "ui_sociobuscar.h"

#include <QKeyEvent>

SocioBuscar::SocioBuscar(QWidget *parent)
                            :QDialog(parent)
                            ,ui(new Ui::SocioBuscar){
    ui->setupUi(this);
    idSocio=INVALIDO;
    setTableView();
    QTimer::singleShot(0, ui->lineEditBuscar, SLOT(setFocus()));
}

SocioBuscar::~SocioBuscar(){
    delete ui;
}

void SocioBuscar::setTableView(){
    QString busqueda="WHERE socios.activado=1";
    BD::buscarSocio(busqueda);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(11);
    model->setHeaderData(0, Qt::Horizontal, tr("# SOCIO"));
    model->setHeaderData(3, Qt::Horizontal, tr("EMPRESA"));
    model->setHeaderData(4, Qt::Horizontal, tr("GRUP FLIA?"));
    model->setHeaderData(5, Qt::Horizontal, tr("CLUB PORVE?"));
    model->setHeaderData(8, Qt::Horizontal, tr("E-M@IL"));
    model->setHeaderData(9, Qt::Horizontal, tr("D.N.I."));
    model->setHeaderData(10, Qt::Horizontal, tr("NACIMIENTO"));    
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
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onPushButtonSeleccionar_clicked()));
    ui->tableView->setVisible(false);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setVisible(true);
}

void SocioBuscar::on_lineEditBuscar_textChanged(const QString &arg1){
    ui->lineEditBuscar->setText(arg1.toUpper());
    QStringList sl = arg1.toUpper().simplified().split(" ");
    QString busquedaNombre = sl.join("%' AND UPPER (socios.nombre) LIKE '%");
    busquedaNombre.prepend("WHERE ( UPPER (socios.nombre) LIKE '%");
    busquedaNombre.append("%' ");
    QString busquedaApellido = sl.join("%' AND UPPER (socios.apellido) LIKE '%");
    busquedaApellido.prepend(" OR  (socios.apellido) LIKE '%");
    busquedaApellido.append("%'  ");
    QString busquedaDni = sl.join("%' AND UPPER (socios.dni) LIKE '%");
    busquedaDni.prepend(" OR  UPPER (socios.dni) LIKE '%");
    busquedaDni.append("%'  ");
    QString busquedaEmpresa = sl.join("%' AND UPPER (empresas.nombre) LIKE '%");
    busquedaEmpresa.prepend(" OR  UPPER (empresas.nombre) LIKE '%");
    busquedaEmpresa.append("%'  ");
    QString busquedaNumSocio = sl.join("%' AND UPPER (socios.idsocio) LIKE '%");
    busquedaNumSocio.prepend(" OR  UPPER (socios.idsocio) LIKE '%");
    busquedaNumSocio.append("%'  ");
    QString busqueda=busquedaNombre+busquedaApellido+busquedaDni+busquedaEmpresa+busquedaNumSocio+") AND (socios.activado=1) ";
    BD::buscarSocio(busqueda);
    model->setHeaderData(0, Qt::Horizontal, tr("# SOCIO"));
    model->setHeaderData(3, Qt::Horizontal, tr("EMPRESA"));
    model->setHeaderData(4, Qt::Horizontal, tr("GRUP FLIA?"));
    model->setHeaderData(5, Qt::Horizontal, tr("CLUB PORVE?"));
    model->setHeaderData(8, Qt::Horizontal, tr("E-M@IL"));
    model->setHeaderData(9, Qt::Horizontal, tr("D.N.I."));
    model->setHeaderData(10, Qt::Horizontal, tr("NACIMIENTO"));
    ui->tableView->setModel(model);
}

void SocioBuscar::onPushButtonSeleccionar_clicked(){
    int row=ui->tableView->selectionModel()->currentIndex().row();
    idSocio=model->data(model->index(row,0), Qt::DisplayRole).toString();
    if (idSocio!=INVALIDO){
        socio.nombre=model->data(model->index(row,1), Qt::DisplayRole).toString();
        socio.apellido=model->data(model->index(row,2), Qt::DisplayRole).toString();  
        empresa.nombre=model->data(model->index(row,3), Qt::DisplayRole).toString();
        socio.grupofamiliar=model->data(model->index(row,4), Qt::DisplayRole).toString();
        socio.clubporve=model->data(model->index(row,5), Qt::DisplayRole).toString();
        socio.telefono=model->data(model->index(row,6), Qt::DisplayRole).toString();
        socio.direccion=model->data(model->index(row,7), Qt::DisplayRole).toString();
        socio.mail=model->data(model->index(row,8), Qt::DisplayRole).toString();
        socio.dni=model->data(model->index(row,9), Qt::DisplayRole).toString();
        socio.fechanac=model->data(model->index(row,10), Qt::DisplayRole).toString();
        socio.flia=model->data(model->index(row,11), Qt::DisplayRole).toString();
        close();
    }
}

void SocioBuscar::on_pushButtonCancelar_clicked(){
    close();
}

void SocioBuscar::keyPressEvent(QKeyEvent * event){
    switch (event->key()){
    case Qt::Key_Escape : close();
        break;
    case Qt::Key_Return : onPushButtonSeleccionar_clicked();
        break;
    case Qt::Key_Up : ui->tableView->selectRow(ui->tableView->selectionModel()->currentIndex().row()-1);
        break;
    case Qt::Key_Down : ui->tableView->selectRow(ui->tableView->selectionModel()->currentIndex().row()+1);
        break;
    }
    QTimer::singleShot(0, ui->lineEditBuscar, SLOT(setFocus()));
}

void SocioBuscar::on_pushButtonImprimir_clicked()
{
    PrintSociosBusqueda *p = new PrintSociosBusqueda();
    p->close();
}
