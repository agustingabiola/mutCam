#include "dialogespera.h"
#include "ui_dialogespera.h"

DialogEspera::DialogEspera(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEspera)
{
    ui->setupUi(this);
    this->setWindowFlags (Qt::Window |Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui->progressBar->setStyleSheet (
            "QProgressBar {"
                "border: 2px solid grey;"
                "border-radius: 5px;"
            "}"
            "QProgressBar::chunk {"
                "background-color: #CD96CD;"
                "width: 10px;"
                "margin: 0.5px;"
            "}"
            "QProgressBar {"
                "border: 2px solid grey;"
                "border-radius: 5px;"
                "text-align: center;}"
            );
    ui->label_imprimiendo->setAlignment (Qt::AlignCenter);
    ui->progressBar->reset ();
}

DialogEspera::~DialogEspera()
{
    delete ui;
}

void DialogEspera::on_aceptar_clicked()
{
    this->close ();
}

void DialogEspera::setAceptar (bool value){
    this->ui->aceptar->setEnabled (value);
}

void DialogEspera::setProgressBar (bool visible){
    if (!visible){
        this->ui->progressBar->hide ();
    }
}

void DialogEspera::setInsideText (QString text){
    this->ui->label_imprimiendo->setText (text);
}

void DialogEspera::on_progressBar_valueChanged(int value)
{
    if (value == 99 || value == 100){
        ui->progressBar->setValue (100);
        ui->aceptar->setEnabled (true);
    }
}

void DialogEspera::updateValue (int value) {
    int x = ui->progressBar->value ();
    if ( x <100){
        x+= value;
        ui->progressBar->setValue (x);
    }
}
