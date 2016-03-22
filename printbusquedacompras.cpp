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
    int count=23;
    while (count<rowCount){
        count=count+23;
        hojas=hojas+1;
    }
    hoja=1;
    hojamax=QString::number(hojas);
    ui->labelHoja->setText("Hoja 1 de "+hojamax);

    ui->tableImpresion->setColumnWidth(0,60);
    ui->tableImpresion->setColumnWidth(1,160);
    ui->tableImpresion->setColumnWidth(2,160);
    ui->tableImpresion->setColumnWidth(3,80);
    ui->tableImpresion->setColumnWidth(4,70);
    ui->tableImpresion->setColumnWidth(5,70);
    ui->tableImpresion->setColumnWidth(6,70);
    ui->tableImpresion->setColumnWidth(7,110);
    ui->tableImpresion->setColumnWidth(8,91);
    ui->tableImpresion->setColumnWidth(9,91);
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
    while (j<rowCount){
        QSqlRecord row = model->record(j);
        ui->tableImpresion->insertRow(i);
        item = new QTableWidgetItem(row.value(1).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 0, item);
        item = new QTableWidgetItem(row.value(2).toString());
        item->setTextAlignment(Qt::AlignLeft);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 1, item);
        item = new QTableWidgetItem(row.value(4).toString());
        item->setTextAlignment(Qt::AlignLeft);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 2, item);
        item = new QTableWidgetItem(row.value(5).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 3, item);
        item = new QTableWidgetItem(row.value(6).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 4, item);
        item = new QTableWidgetItem(row.value(7).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 5, item);
        item = new QTableWidgetItem(row.value(8).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 6, item);
        item = new QTableWidgetItem(row.value(9).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 7, item);
        item = new QTableWidgetItem(row.value(10).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 8, item);
        item = new QTableWidgetItem(row.value(11).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 9, item);
        j++;
        i++;
        if (i==23){
            i=0;
            if (hoja>1){
                printer.newPage();
            }
            render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
            hoja++;
            ui->tableImpresion->clear();
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
