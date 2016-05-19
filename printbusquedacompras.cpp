#include "printbusquedacompras.h"
#include "ui_printbusquedacompras.h"
#include <QDebug>
PrintBusquedaCompras::PrintBusquedaCompras(QWidget *parent, QString nota) :
    QWidget(parent),
    ui(new Ui::PrintBusquedaCompras)
{
    ui->setupUi(this);

    ui->labelNotas->setText(nota);
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

    ui->tableImpresion->setColumnWidth(0,80);
    ui->tableImpresion->setColumnWidth(1,200);
    ui->tableImpresion->setColumnWidth(2,80);
    ui->tableImpresion->setColumnWidth(3,70);
    ui->tableImpresion->setColumnWidth(4,70);
    ui->tableImpresion->setColumnWidth(5,80);
    ui->tableImpresion->setColumnWidth(6,170);
    ui->tableImpresion->setColumnWidth(7,110);
    ui->tableImpresion->setColumnWidth(8,110);
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
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOrientation(QPrinter::Landscape);
    QString fileNameAndPath = QFileDialog::getSaveFileName(
        this,
        "Guardar en formato PDF",
        "busquedaCompras",
        "*.pdf"
    );
    if (!fileNameAndPath.isNull()) {
        printer.setOutputFileName(fileNameAndPath);
    } else {
        delete ui;
        close();
        return;
    }
    QPainter painter(&printer);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    while (j<rowCount){
        QSqlRecord row = model->record(j);
        ui->tableImpresion->insertRow(i);
        item = new QTableWidgetItem(row.value(1).toString());
        item->setTextAlignment(Qt::AlignLeft);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 0, item);
        item = new QTableWidgetItem(row.value(4).toString());
        item->setTextAlignment(Qt::AlignLeft);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 1, item);
        item = new QTableWidgetItem(row.value(5).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 2, item);
        item = new QTableWidgetItem(row.value(6).toString());
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 3, item);
        item = new QTableWidgetItem(row.value(7).toString());
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 4, item);
        item = new QTableWidgetItem(row.value(8).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 5, item);
        item = new QTableWidgetItem(row.value(9).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 6, item);
        item = new QTableWidgetItem(row.value(10).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 7, item);
        item = new QTableWidgetItem(row.value(11).toString());
        item->setTextAlignment(Qt::AlignRight);
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

PrintBusquedaCompras::~PrintBusquedaCompras()
{
    delete ui;
}
