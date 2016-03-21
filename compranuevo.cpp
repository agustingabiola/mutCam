#include "compranuevo.h"
#include "ui_compranuevo.h"

CompraNuevo::CompraNuevo(QWidget *parent)
                      :QDialog(parent)
                      ,ui(new Ui::CompraNuevo){
    ui->setupUi(this);
    idCompra=INVALIDO;
    conectarCheckBoxes();
    setLineEditMonto();
    setTabOrder(ui->pushButtonSocio,ui->pushButtonPrestador);
    setTabOrder(ui->pushButtonPrestador,ui->comboBox);
    setTabOrder(ui->comboBox,ui->lineEditMonto);
    setTabOrder(ui->lineEditMonto,ui->lineEditMontoDec);
    setTabOrder(ui->lineEditMontoDec,ui->spinBox);
    setTabOrder(ui->spinBox,ui->spinBoxAct);
    setTabOrder(ui->spinBoxAct,ui->dateEdit);
    setTabOrder(ui->dateEdit,ui->lineEditObservaciones);
    setTabOrder(ui->lineEditObservaciones,ui->pushButtonAgregar);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMaximumDate(QDate::currentDate());
}

CompraNuevo::~CompraNuevo(){
    delete ui;
}

void CompraNuevo::setLineEditMonto(){
    QRegExp rx("[0-9]{5,5}");
    ui->lineEditMonto->setValidator(new QRegExpValidator(rx, ui->lineEditMonto));
    QRegExp rx1("[0-9]{2,2}");
    ui->lineEditMontoDec->setValidator(new QRegExpValidator(rx1, ui->lineEditMontoDec));
}


void CompraNuevo::conectarCheckBoxes(){
    connect(ui->checkBoxSocio, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxNumSocio, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxPrestador, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxTipo, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxObservaciones, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
}

void CompraNuevo::todosChequeados(){
    if (ui->checkBoxSocio->isChecked() &&
            ui->checkBoxNumSocio->isChecked() &&
            ui->checkBoxPrestador->isChecked() &&
            ui->checkBoxTipo->isChecked() &&
            ui->checkBoxObservaciones->isChecked() &&
            (ui->spinBox->value()>=ui->spinBoxAct->value())){
        ui->pushButtonAgregar->setEnabled(true);
    }else
        ui->pushButtonAgregar->setEnabled(false);
}


void CompraNuevo::on_lineEditObservaciones_textEdited(const QString &arg1){
    QString s=arg1.simplified();
    if (s.length()<=50){
        ui->checkBoxObservaciones->setEnabled(true);
        ui->checkBoxObservaciones->setChecked(true);
        ui->labelComentario->setText("");
    }else{
        ui->labelComentario->setText("El campo Observaciones no puede superar los 50 caracteres");
        ui->checkBoxObservaciones->setChecked(false);
        ui->checkBoxObservaciones->setDisabled(true);
    }
}

void CompraNuevo::on_pushButtonSocio_clicked(){
    socioBuscar=new SocioBuscar();
    socioBuscar->exec();
    if (idSocio!=INVALIDO){
        showNormal();
        raise();
        activateWindow();
        ui->lineEditSocio->setText(socio.nombre+" "+socio.apellido);
        ui->lineEditDni->setText(socio.dni);
        ui->lineEditNumSocio->setText(idSocio);
        ui->checkBoxNumSocio->setEnabled(true);
        ui->checkBoxSocio->setEnabled(true);
        ui->checkBoxNumSocio->setChecked(true);
        ui->checkBoxSocio->setChecked(true);
    }
}

void CompraNuevo::on_pushButtonPrestador_clicked(){
    prestadorBuscar=new PrestadorBuscar();
    prestadorBuscar->exec();
    if (idPrestador!=INVALIDO){
        showNormal();
        raise();
        activateWindow();
        ui->lineEditPrestador->setText(prestador.nombre);
        ui->checkBoxPrestador->setEnabled(true);
        ui->checkBoxPrestador->setChecked(true);
    }
}

void CompraNuevo::on_pushButtonAgregar_clicked(){
    if (ui->spinBox->value()>=ui->spinBoxAct->value()){
        setDisabled(true);
        cargarAttributosCompra();
        BD::agregarCompra();
        exit();
    }else
        ui->labelComentario->setText("La cuota actual no puede ser mayor a la cantidad de cuotas!!!");
}

void CompraNuevo::cargarAttributosCompra(){
    compra.cantcuotas=QString::number(ui->spinBox->value());
    compra.cuotaact=QString::number(ui->spinBoxAct->value());
    QString entero;
    QString decimal;
    if (ui->lineEditMonto->text()=="")
        entero="0";
    else
        entero=ui->lineEditMonto->text();
    if (ui->lineEditMontoDec->text()=="")
        decimal="0";
    else
        decimal=ui->lineEditMontoDec->text();
    if (entero=="0" && decimal=="0")
        compra.monto="0";
    else
        compra.monto=entero+"."+decimal;
    qDebug()<<compra.monto;
    compra.fechaautorizacion=ui->dateEdit->date().toString("dd-MM-yyyy");
    compra.fechamodificacion=ui->dateEdit->date().toString("dd-MM-yyyy");
    compra.observaciones=ui->lineEditObservaciones->text().simplified();
    compra.terminado="0";
    compra.tipo=ui->comboBox->currentText();
}

void CompraNuevo::on_pushButtonCancelar_clicked(){
    exit();
}

void CompraNuevo::exit(){
    emit compraNuevoTerminado();
    idCompra=INVALIDO;
    this->close();
}
