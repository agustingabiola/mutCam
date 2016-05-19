#include "printempresabusqueda.h"
#include "ui_printempresabusqueda.h"

PrintEmpresaBusqueda::PrintEmpresaBusqueda(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintEmpresaBusqueda)
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

    ui->tableImpresion->setColumnWidth(0,275);
    ui->tableImpresion->setColumnWidth(1,150);
    ui->tableImpresion->setColumnWidth(2,185);
    ui->tableImpresion->setColumnWidth(3,100);
    ui->tableImpresion->setColumnWidth(4,210);
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
        "listadoEmpresasAl_" + QDate::currentDate().toString("dd_MM_yy"),
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
    QFont f = QFont();
    f.setPixelSize(12);
    while (j<rowCount){
        QSqlRecord row = model->record(j);
        ui->tableImpresion->insertRow(i);
        item = new QTableWidgetItem(row.value(2).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 0, item);
        item = new QTableWidgetItem(row.value(3).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 1, item);
        item = new QTableWidgetItem(row.value(4).toString());
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        item->setFont(f);
        ui->tableImpresion->setItem(i, 2, item);
        item = new QTableWidgetItem(row.value(5).toString());
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        item->setFont(f);
        ui->tableImpresion->setItem(i, 3, item);
        item = new QTableWidgetItem(row.value(6).toString());
        item->setFont(f);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableImpresion->setItem(i, 4, item);
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

PrintEmpresaBusqueda::~PrintEmpresaBusqueda()
{
    delete ui;
}
