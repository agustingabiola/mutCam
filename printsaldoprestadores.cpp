#include "printsaldoprestadores.h"
#include "ui_printsaldoprestadores.h"

PrintSaldoPrestadores::PrintSaldoPrestadores(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintSaldoPrestadores)
{
    ui->setupUi(this);

    ui->labelFecha->setText("FECHA: " + QDate::currentDate().toString("dd/MM/yy"));

    int hojas=1;
    while(model->canFetchMore()) {
        model->fetchMore();
    }
    int rowCount= model->rowCount();
    int count=27;
    while (count<rowCount){
        count=count+27;
        hojas=hojas+1;
    }
    hoja=1;
    hojamax=QString::number(hojas);
    ui->labelHoja->setText("Hoja 1 de "+hojamax);

    ui->tableImpresion->setColumnWidth(0,300);
    ui->tableImpresion->setColumnWidth(1,300);
    ui->tableImpresion->setColumnWidth(2,100);
    ui->tableImpresion->setColumnWidth(3,120);
    ui->tableImpresion->setColumnWidth(4,120);
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
                         "font-size: 10px; }";
    ui->tableImpresion->horizontalHeader()->setStyleSheet(styleSheet);

    int j=0;
    int i=0;
    double total = 0;
    QTableWidgetItem *item;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOrientation(QPrinter::Landscape);
    QString fileNameAndPath = QFileDialog::getSaveFileName(
        this,
        "Guardar en formato PDF",
        "saldoAcreedor" + QDate::currentDate().toString("dd_MM_yy"),
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
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 0, item);
        item = new QTableWidgetItem(row.value(2).toString());
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 1, item);
        item = new QTableWidgetItem(row.value(3).toString());
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 2, item);
        item = new QTableWidgetItem(row.value(4).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 3, item);
        item = new QTableWidgetItem(row.value(5).toString());
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 4, item);
        total += row.value(5).toDouble();
        j++;
        i++;
        if (i==27){
            i=0;
            if (j == rowCount) {
                ui->label_textAclaracion->show();
                ui->label_textTotal->show();
                ui->labelTotal->show();
                ui->labelTotal->setText(QString::number(total));
            } else {
                ui->label_textAclaracion->hide();
                ui->label_textTotal->hide();
                ui->labelTotal->hide();
            }

            render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
            printer.newPage();
            hoja++;
            ui->tableImpresion->clearContents();
            ui->labelHoja->setText("Hoja "+QString::number(hoja)+" de "+hojamax);
        }
    }

    if (i>0) {
        ui->label_textAclaracion->show();
        ui->label_textTotal->show();
        ui->labelTotal->show();
        ui->labelTotal->setText(QString::number(total));
        render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    }
    painter.end();
    delete ui;
    close();
}

PrintSaldoPrestadores::~PrintSaldoPrestadores()
{
    delete ui;
}
