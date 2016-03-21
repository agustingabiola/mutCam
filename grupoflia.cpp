#include "grupoflia.h"
#include "ui_grupoflia.h"

GrupoFlia::GrupoFlia(QWidget *parent)
                      :QDialog(parent)
                      ,ui(new Ui::GrupoFlia){
    ui->setupUi(this);  
    ui->tableWidget->setColumnWidth(0,400);
    ui->tableWidget->setColumnWidth(1,400);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,75);
    ui->tableWidget->setColumnWidth(4,150);
    ui->tableWidget->setColumnWidth(5,150);
    QString styleSheet ="QHeaderView::section {"
                            "spacing: 10px;"
                            "background-color: lightblue;"
                            "color: black;"
                            "border: 1px solid black;"
                            "margin: 1px;"
                            "height: 30px;"
                            "text-align: right;"
                            "font-family: arialblack;"
                            "font-size: 20px; }";
    ui->tableWidget->horizontalHeader()->setStyleSheet(styleSheet);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    if (socio.flia!=""){
        QStringList sl=socio.flia.split(SEPARADOR_TEXTO);
        int indice=1;
        int a=sl.size()/6;
        QTableWidgetItem *item;
        for (int r=0; r<a; r++){
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            for (int c=0; c<6; c++){
                item = new QTableWidgetItem(sl.at(indice));
                item->setTextAlignment(Qt::AlignLeft);
                ui->tableWidget->setItem(r, c, item);
                indice++;
            }
        }
    }
}

GrupoFlia::~GrupoFlia(){
    delete ui;
}

void GrupoFlia::on_pushButtonAceptar_clicked(){
    //QModelIndex index = ui->tableWidget->currentIndex();
    ui->tableWidget->setCurrentIndex(QModelIndex());
    //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setDisabled(true);
    QTimer::singleShot(0, ui->pushButtonAceptar, SLOT(setFocus()));
    QString s="";
    QTableWidgetItem *item;
    for (int r=0; r<ui->tableWidget->rowCount(); r++)
        for (int c=0; c<6; c++){
            item = ui->tableWidget->item(r, c);
            if(item)
                s.append(SEPARADOR_TEXTO+ui->tableWidget->item(r,c)->text());
            else
                s.append(SEPARADOR_TEXTO);
        }
    s.append(SEPARADOR_TEXTO);
    socio.flia=s;
    exit();
}

void GrupoFlia::on_pushButtonEliminar_clicked(){
    int rowa=ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(rowa);
}

void GrupoFlia::on_pushButtonAgregar_clicked(){
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
}

void GrupoFlia::on_pushButtonCancelar_clicked(){
    exit();
}

void GrupoFlia::exit(){
    this->close();
}
