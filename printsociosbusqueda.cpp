#include "printsociosbusqueda.h"
#include "ui_printsociosbusqueda.h"

DialogEspera* PrintSociosBusqueda::d_espera;

PrintSociosBusqueda::PrintSociosBusqueda(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintSociosBusqueda)
{
    ui->setupUi(this);

    ui->labelFecha->setText("FECHA: " + QDate::currentDate().toString("dd/MM/yy"));

    d_espera = new DialogEspera();
    d_espera->setModal (true);
    d_espera->setWindowTitle("Imprimiendo");
    d_espera->setInsideText("Imprimiendo socios");
    d_espera->updateValue(1);
    d_espera->show ();

    int hojas=1;
    while(model->canFetchMore()) {
        model->fetchMore();
    }
    int rowCount= model->rowCount();
    int maxRowsPerPage = 27;
    int count=maxRowsPerPage;
    while (count<rowCount){
        count=count+maxRowsPerPage;
        hojas=hojas+1;
    }
    hoja=1;
    hojamax=QString::number(hojas);
    progressIncrement = static_cast<int>(((100/ hojas)+0.5f));
    ui->labelHoja->setText("Hoja 1 de "+hojamax);

    ui->tableImpresion->setColumnWidth(0,170);
    ui->tableImpresion->setColumnWidth(1,175);
    ui->tableImpresion->setColumnWidth(2,40);
    ui->tableImpresion->setColumnWidth(3,40);
    ui->tableImpresion->setColumnWidth(4,75);
    ui->tableImpresion->setColumnWidth(5,175);
    ui->tableImpresion->setColumnWidth(6,175);
    ui->tableImpresion->setColumnWidth(7,65);
    ui->tableImpresion->setColumnWidth(8,65);
    QString styleSheet = "QHeaderView::section {"
                         "spacing: 5px;"
                         "height: 23px;"
                         "background-color: darkcyan;"
                         "color: black;"
                         "border: 1px solid black;"
                         "margin: 0px;"
                         "text-align: right;"
                         "font-family: arialblack;"
                         "font: bold 12px;"
                         "font-size: 12px; }";
    ui->tableImpresion->horizontalHeader()->setStyleSheet(styleSheet);

    int j=0;
    int i=0;
    QTableWidgetItem *item;
    printer.setOrientation(QPrinter::Landscape);
    QPainter painter(&printer);
    QFont f = QFont();
    f.setPixelSize(10);
    QApplication::processEvents();
    while (j<rowCount){
        QSqlRecord row = model->record(j);
        ui->tableImpresion->insertRow(i);
        item = new QTableWidgetItem(row.value(1).toString() + " " + row.value(2).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 0, item);
        item = new QTableWidgetItem(row.value(3).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 1, item);
        item = new QTableWidgetItem(row.value(4).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 2, item);
        item = new QTableWidgetItem(row.value(5).toString());
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        item->setFont(f);
        ui->tableImpresion->setItem(i, 3, item);
        item = new QTableWidgetItem(row.value(6).toString());
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        item->setFont(f);
        ui->tableImpresion->setItem(i, 4, item);
        item = new QTableWidgetItem(row.value(7).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 5, item);
        item = new QTableWidgetItem(row.value(8).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 6, item);
        item = new QTableWidgetItem(row.value(9).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 7, item);
        item = new QTableWidgetItem(row.value(10).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 8, item);
        j++;
        i++;
        if (i==maxRowsPerPage){
            i=0;
            render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
            printer.newPage();
            hoja++;
            ui->tableImpresion->clearContents();
            d_espera->updateValue(progressIncrement);
            QApplication::processEvents();
            ui->labelHoja->setText("Hoja "+QString::number(hoja)+" de "+hojamax);
        }
    }

    if (i>0) {
        render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
        QApplication::processEvents();
    }
    painter.end();
    d_espera->close();
    delete ui;
    close();
}

PrintSociosBusqueda::~PrintSociosBusqueda()
{
    delete ui;
}
