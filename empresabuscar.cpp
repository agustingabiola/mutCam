#include "empresabuscar.h"
#include "ui_empresabuscar.h"

#include <QKeyEvent>

EmpresaBuscar::EmpresaBuscar(QWidget *parent)
                            :QDialog(parent)
                            ,ui(new Ui::EmpresaBuscar){
    ui->setupUi(this);
    idEmpresa=INVALIDO;
    setTableView();
    QTimer::singleShot(0, ui->lineEditBuscar, SLOT(setFocus()));
}

EmpresaBuscar::~EmpresaBuscar(){
    delete ui;
}

void EmpresaBuscar::setTableView(){
    QString busqueda="WHERE activado=1";
    BD::buscarEmpresa(busqueda);
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

void EmpresaBuscar::on_lineEditBuscar_textChanged(const QString &arg1){
    ui->lineEditBuscar->setText(arg1.toUpper());
    QStringList sl = arg1.toUpper().simplified().split(" ");
    QString busquedaRazonSocial = sl.join("%' AND UPPER (razon_social) LIKE '%");
    busquedaRazonSocial.prepend("WHERE ( ( UPPER (razon_social) LIKE '%");
    busquedaRazonSocial.append("%' ) ");
    QString busquedaCuit = sl.join("%' AND UPPER (cuit) LIKE '%");
    busquedaCuit.prepend(" OR ( UPPER (cuit) LIKE '%");
    busquedaCuit.append("%'  ) ");
    QString busquedaDireccion = sl.join("%' AND UPPER (direccion) LIKE '%");
    busquedaDireccion.prepend(" OR ( UPPER (direccion) LIKE '%");
    busquedaDireccion.append("%'  ) ");
    QString busquedaNombre = sl.join("%' AND UPPER (nombre) LIKE '%");
    busquedaNombre.prepend(" OR ( UPPER (nombre) LIKE '%");
    busquedaNombre.append("%' ) ");
    QString busqueda=busquedaRazonSocial+busquedaCuit+busquedaDireccion+busquedaNombre+" ) AND (activado=1) ";
    BD::buscarEmpresa(busqueda);
    model->setHeaderData(2, Qt::Horizontal, tr("RAZON SOCIAL"));
    model->setHeaderData(4, Qt::Horizontal, tr("E-M@IL"));
    ui->tableView->setModel(model);
}

void EmpresaBuscar::on_pushButtonNuevoEmpresa_clicked(){
    empresaNuevo = new EmpresaNueva();
    empresaNuevo->exec();
    if (idEmpresa!=INVALIDO)
        close();
    on_lineEditBuscar_textChanged(ui->lineEditBuscar->text());
}

void EmpresaBuscar::on_pushButtonSeleccionar_clicked(){
    int row=ui->tableView->selectionModel()->currentIndex().row();
    idEmpresa=model->data(model->index(row,0), Qt::DisplayRole).toString();
    if (idEmpresa!=INVALIDO){
        empresa.razon_social=model->data(model->index(row,2), Qt::DisplayRole).toString();
        empresa.nombre=model->data(model->index(row,1), Qt::DisplayRole).toString();
        empresa.telefono=model->data(model->index(row,3), Qt::DisplayRole).toString();
        empresa.mail=model->data(model->index(row,4), Qt::DisplayRole).toString();
        empresa.cuit=model->data(model->index(row,5), Qt::DisplayRole).toString();
        empresa.direccion=model->data(model->index(row,6), Qt::DisplayRole).toString();
        close();
    }
}

void EmpresaBuscar::on_pushButtonCancelar_clicked(){
    idEmpresa=INVALIDO;
    close();
}

void EmpresaBuscar::on_pushButtonEliminar_clicked(){
    int row=ui->tableView->selectionModel()->currentIndex().row();
    idEmpresa=model->data(model->index(row,0), Qt::DisplayRole).toString();
    if (idEmpresa!=INVALIDO){
        empresa.razon_social=model->data(model->index(row,2), Qt::DisplayRole).toString();
        empresa.nombre=model->data(model->index(row,1), Qt::DisplayRole).toString();
        empresa.telefono=model->data(model->index(row,3), Qt::DisplayRole).toString();
        empresa.mail=model->data(model->index(row,4), Qt::DisplayRole).toString();
        empresa.cuit=model->data(model->index(row,5), Qt::DisplayRole).toString();
        empresa.direccion=model->data(model->index(row,6), Qt::DisplayRole).toString();
        QMessageBox::StandardButton reply;
        reply=QMessageBox::information(this, "Desea Continuar?"
                                  , "Si continua se borrara esta EMPRESA permanentemente. \n"
                                    "y ademas se borraran todos SOCIOS relacionadas con la misma y todas las COMPRAS echas por dichos SOCIOS. \n"
                                    "En caso afirmativo se le pedira otra confirmacion"
                                  , QMessageBox::Ok|QMessageBox::No);
        if (reply==QMessageBox::Ok){
            reply=QMessageBox::critical(this, "Esta Seguro Que Desea Continuar?"
                                         , "Si continua borrara esta EMPRESA permanentemente \n"
                                           "y ademas se borraran todos SOCIOS relacionadas con la misma y todas las COMPRAS echas por dichos SOCIOS. \n"
                                           "Esta accion no se puede deshacer."
                                         , QMessageBox::Ok|QMessageBox::No);
            if (reply==QMessageBox::Ok){
                BD::eliminarEmpresa();
            }
        }
    }
    on_lineEditBuscar_textChanged(ui->lineEditBuscar->text());
}

void EmpresaBuscar::keyPressEvent(QKeyEvent * event){
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
