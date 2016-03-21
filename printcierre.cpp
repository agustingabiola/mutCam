#include "printcierre.h"
#include "ui_printcierre.h"
#include <QFileDialog>
#include <QPrintDialog>
#include <QDebug>
#include "qstringmoney.h"

PrintCierre::PrintCierre(QStringList id,
                           QStringList apellido,
                           QStringList nombre,
                           QStringList dni,
                           QStringList cuotasocio,
                           QStringList grupofamiliar,
                           QStringList cuotaclub,
                           QStringList compras,
                           QStringList cheques,
                           QStringList totales,
                           QString pathy,
                           double t,
                           QWidget *parent) :
                           QWidget(parent),
                           ui(new Ui::PrintCierre){
    ui->setupUi(this);
    ui->labelEmpresa->setText(empresa.nombre);
    ui->labelCuit->setText(empresa.cuit);
    ui->labelDomicilio->setText(empresa.direccion);
    ui->labelTelefono->setText(empresa.telefono);
    ui->labelMail->setText(empresa.mail);
    ui->labelFecha->setText("FECHA: "+QDate::currentDate().toString("dd/MM/yy"));
    int hojas=1;
    int size=apellido.size();
    int cont=23;
    while (cont<size){
        cont=cont+23;
        hojas=hojas+1;
    }
    hoja=1;
    hojamax=QString::number(hojas);
    ui->labelHoja->setText("Hoja 1 de "+hojamax);

    model = new QStandardItemModel();
    ui->tableSocios->setColumnWidth(0,60);
    ui->tableSocios->setColumnWidth(1,160);
    ui->tableSocios->setColumnWidth(2,160);
    ui->tableSocios->setColumnWidth(3,80);
    ui->tableSocios->setColumnWidth(4,78);
    ui->tableSocios->setColumnWidth(5,78);
    ui->tableSocios->setColumnWidth(6,78);
    ui->tableSocios->setColumnWidth(7,86);
    ui->tableSocios->setColumnWidth(8,86);
    ui->tableSocios->setColumnWidth(9,91);
    QString styleSheet = "QHeaderView::section {"
                         "spacing: 10px;"
                         "height: 23px;"
                         "background-color: darkcyan;"
                         "color: black;"
                         "border: 1px solid black;"
                         "margin: 0px;"
                         "text-align: right;"
                         "font-family: arialblack;"
                         "font: bold 12px;"
                         "font-size: 12px; }";
    ui->tableSocios->horizontalHeader()->setStyleSheet(styleSheet);

    QString filename = pathy; //+"_H"+QString::number(hoja)+"_"+hojamax+".pdf";
    if(!filename.isEmpty()) {
        if(QFileInfo(filename).suffix().isEmpty()) {
            filename.append(".pdf");
        }
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);
        printer.setOrientation(QPrinter::Landscape);
    }
    QPainter painter(&printer);
    int j=0;
    int i=0;
    bool es23=false;
    QTableWidgetItem *item;
    while (j<id.size()){
        es23=false;
        ui->tableSocios->insertRow(i);
        item = new QTableWidgetItem(id.at(j));
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableSocios->setItem(i, 0, item);
        item = new QTableWidgetItem(apellido.at(j));
        item->setTextAlignment(Qt::AlignLeft);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableSocios->setItem(i, 1, item);
        item = new QTableWidgetItem(nombre.at(j));
        item->setTextAlignment(Qt::AlignLeft);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableSocios->setItem(i, 2, item);
        item = new QTableWidgetItem(dni.at(j));
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableSocios->setItem(i, 3, item);
        item = new QTableWidgetItem(cuotasocio.at(j));
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableSocios->setItem(i, 4, item);
        item = new QTableWidgetItem(grupofamiliar.at(j));
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableSocios->setItem(i, 5, item);
        item = new QTableWidgetItem(cuotaclub.at(j));
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableSocios->setItem(i, 6, item);
        item = new QTableWidgetItem(compras.at(j));
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableSocios->setItem(i, 7, item);
        item = new QTableWidgetItem(cheques.at(j));
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableSocios->setItem(i, 8, item);
        item = new QTableWidgetItem(totales.at(j));
        item->setTextAlignment(Qt::AlignRight);
        item->setFlags(item->flags()&~Qt::ItemIsEditable);
        ui->tableSocios->setItem(i, 9, item);
        j++;
        i++;
        if (i==23){
            i=0;
            es23=true;
            if (hoja>1){
                printer.newPage();
            }
            this->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
            hoja++;
            ui->tableSocios->clear();
            ui->labelHoja->setText("Hoja "+QString::number(hoja)+" de "+hojamax);
        }
    }

    ui->tableSocios->insertRow(i);
    item = new QTableWidgetItem("TOTAL:");
    item->setTextAlignment(Qt::AlignRight);
    item->setFlags(item->flags()&~Qt::ItemIsEditable);
    ui->tableSocios->setItem(i, 8, item);

    item = new QTableWidgetItem(QStringMoney::number(t));
    item->setTextAlignment(Qt::AlignRight);
    item->setFlags(item->flags()&~Qt::ItemIsEditable);
    ui->tableSocios->setItem(i, 9, item);

    i++;

    if (i==23){
        i=0;
        es23=true;
        if (hoja>1){
            printer.newPage();
        }
        this->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
        hoja++;
        ui->tableSocios->clear();
        ui->labelHoja->setText("Hoja "+QString::number(hoja)+" de "+hojamax);
    }

    if (!es23){
        if (hoja>1){
            printer.newPage();
        }
        this->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    }
    painter.end();
    //delete ui;
    close();

/*
    if (i==23){
        if (hoja>1){
            printer.newPage();
        }
    }
    this->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    painter.end();
    delete ui;
    close();*/
}

PrintCierre::~PrintCierre(){
    delete ui;
}

void PrintCierre::printAux(QString pathy){
}

QString PrintCierre::getTotal(QStringList totals){
    int i=0;
    double d = 0;
    while (i<totals.length()){
        d = d + totals.at(i).toDouble();
    }
    return QStringMoney::number(d);
}
