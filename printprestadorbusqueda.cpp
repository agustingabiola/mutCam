#include "printprestadorbusqueda.h"
#include "ui_printprestadorbusqueda.h"

PrintPrestadorBusqueda::PrintPrestadorBusqueda(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintPrestadorBusqueda)
{
    ui->setupUi(this);

    ui->labelFecha->setText("FECHA: " + QDate::currentDate().toString("dd/MM/yy"));

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
    ui->labelHoja->setText("Hoja 1 de "+hojamax);

    ui->tableImpresion->setColumnWidth(0,200);
    ui->tableImpresion->setColumnWidth(1,220);
    ui->tableImpresion->setColumnWidth(2,105);
    ui->tableImpresion->setColumnWidth(3,125);
    ui->tableImpresion->setColumnWidth(4,90);
    ui->tableImpresion->setColumnWidth(5,180);
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
    f.setPixelSize(12);
    while (j<rowCount){
        QSqlRecord row = model->record(j);
        ui->tableImpresion->insertRow(i);
        item = new QTableWidgetItem(row.value(1).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 0, item);
        item = new QTableWidgetItem(row.value(2).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 1, item);
        item = new QTableWidgetItem(row.value(3).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 2, item);
        item = new QTableWidgetItem(row.value(4).toString());
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        item->setFont(f);
        ui->tableImpresion->setItem(i, 3, item);
        item = new QTableWidgetItem(row.value(5).toString());
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        item->setFont(f);
        ui->tableImpresion->setItem(i, 4, item);
        item = new QTableWidgetItem(row.value(6).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 5, item);
        j++;
        i++;
        if (i==maxRowsPerPage){
            i=0;
            render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
            printer.newPage();
            hoja++;
            ui->tableImpresion->clearContents();
            ui->labelHoja->setText("Hoja "+QString::number(hoja)+" de "+hojamax);
        }
    }

    if (i>0) {
        render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    }
    painter.end();
    delete ui;
    close();
}

PrintPrestadorBusqueda::~PrintPrestadorBusqueda()
{
    delete ui;
}
