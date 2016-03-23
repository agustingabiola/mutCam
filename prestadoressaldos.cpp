#include "prestadoressaldos.h"
#include "ui_prestadoressaldos.h"

PrestadoresSaldos::PrestadoresSaldos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrestadoresSaldos)
{
    ui->setupUi(this);
    idPrestador=INVALIDO;
    setTableView();
    QTimer::singleShot(0, ui->lineEditBuscar, SLOT(setFocus()));
}

PrestadoresSaldos::~PrestadoresSaldos()
{
    delete ui;
}

void PrestadoresSaldos::on_pushButtonImprimir_clicked()
{
    PrintSaldoPrestadores *p = new PrintSaldoPrestadores();
    p->close();
}

void PrestadoresSaldos::on_pushButtonCancelar_clicked()
{
    idPrestador=INVALIDO;
    close();
}

void PrestadoresSaldos::setTableView()
{
    QString busqueda="WHERE activado=1";
    BD::buscarSaldoPrestadores(busqueda);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    model->setHeaderData(2, Qt::Horizontal, tr("NOMBRE DEL COMPRADOR"));
    model->setHeaderData(1, Qt::Horizontal, tr("RAZON SOCIAL"));
    model->setHeaderData(3, Qt::Horizontal, tr("#COMPRA"));
    model->setHeaderData(4, Qt::Horizontal, tr("CUOTAS ADEUDADAS"));
    model->setHeaderData(5, Qt::Horizontal, tr("MONTO MENSUAL"));
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
    ui->tableView->setColumnWidth(1,300);
    ui->tableView->setColumnWidth(2,300);
    ui->tableView->setColumnWidth(3,120);
    ui->tableView->setColumnWidth(4,200);
    ui->tableView->setColumnWidth(5,200);
    ui->tableView->setVisible(true);
}

void PrestadoresSaldos::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()){
        case Qt::Key_Escape : close();
            break;
        case Qt::Key_Up : ui->tableView->selectRow(ui->tableView->selectionModel()->currentIndex().row()-1);
            break;
        case Qt::Key_Down : ui->tableView->selectRow(ui->tableView->selectionModel()->currentIndex().row()+1);
            break;
    }
    QTimer::singleShot(0, ui->lineEditBuscar, SLOT(setFocus()));
}

void PrestadoresSaldos::on_lineEditBuscar_textChanged(const QString &arg1)
{
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
    BD::buscarSaldoPrestadores(busqueda);
    model->setHeaderData(2, Qt::Horizontal, tr("NOMBRE DEL COMPRADOR"));
    model->setHeaderData(1, Qt::Horizontal, tr("RAZON SOCIAL"));
    model->setHeaderData(3, Qt::Horizontal, tr("#COMPRA"));
    model->setHeaderData(4, Qt::Horizontal, tr("CUOTAS ADEUDADAS"));
    model->setHeaderData(5, Qt::Horizontal, tr("MONTO MENSUAL"));
    ui->tableView->setModel(model);
}
