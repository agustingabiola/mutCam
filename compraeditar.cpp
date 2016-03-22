#include "compraeditar.h"
#include "ui_compraeditar.h"

CompraEditar::CompraEditar(QWidget *parent)
                      :QDialog(parent)
                      ,ui(new Ui::CompraEditar){
    ui->setupUi(this);
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
    ui->dateEdit->setMaximumDate(QDate::currentDate());
    origIdPrestador = idPrestador;
    origNombrePrestador = prestador.nombre;
    origIdSocio = idSocio;
    origNombreSocio = socio.nombre;
    load();
    editado=false;
}

CompraEditar::~CompraEditar(){
    delete ui;
}

void CompraEditar::setLineEditMonto(){
    QRegExp rx("[0-9]{5,5}");
    ui->lineEditMonto->setValidator(new QRegExpValidator(rx, ui->lineEditMonto));
    QRegExp rx1("[0-9]{2,2}");
    ui->lineEditMontoDec->setValidator(new QRegExpValidator(rx1, ui->lineEditMontoDec));
}


void CompraEditar::conectarCheckBoxes(){
    connect(ui->checkBoxSocio, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxNumSocio, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxPrestador, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxTipo, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxObservaciones, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->lineEditMonto, SIGNAL(textChanged(QString)), this, SLOT(fieldEdited()));
    connect(ui->lineEditMontoDec, SIGNAL(textChanged(QString)), this, SLOT(fieldEdited()));
    connect(ui->spinBox, SIGNAL(valueChanged(QString)), this, SLOT(fieldEdited()));
    connect(ui->spinBoxAct, SIGNAL(valueChanged(QString)), this, SLOT(fieldEdited()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(fieldEdited()));
}

void CompraEditar::fieldEdited() {
    editado = true;
    todosChequeados();
}

void CompraEditar::todosChequeados(){
    if (ui->checkBoxSocio->isChecked() &&
            ui->checkBoxNumSocio->isChecked() &&
            ui->checkBoxPrestador->isChecked() &&
            ui->checkBoxTipo->isChecked() &&
            ui->checkBoxObservaciones->isChecked() &&
            (ui->spinBox->value()>=ui->spinBoxAct->value()) &&
            editado){
        ui->pushButtonAgregar->setEnabled(true);
    }else
        ui->pushButtonAgregar->setEnabled(false);
}


void CompraEditar::on_lineEditObservaciones_textEdited(const QString &arg1){
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
    editado=true;
}

void CompraEditar::on_pushButtonSocio_clicked(){
    socioBuscar=new SocioBuscar();
    socioBuscar->exec();
    if (idSocio!=INVALIDO){
        showNormal();
        raise();
        activateWindow();
        ui->lineEditSocio->setText(socio.nombre+" "+socio.apellido);
        ui->lineEditNumSocio->setText(idSocio);
        ui->checkBoxNumSocio->setEnabled(true);
        ui->checkBoxSocio->setEnabled(true);
        ui->checkBoxNumSocio->setChecked(true);
        ui->checkBoxSocio->setChecked(true);
    }
    editado=true;
}

void CompraEditar::on_pushButtonPrestador_clicked(){
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
    editado=true;
}

void CompraEditar::on_pushButtonAgregar_clicked(){
    if (ui->spinBox->value()>=ui->spinBoxAct->value()){
        setDisabled(true);
        cargarAttributosCompra();
        BD::actualizarCompra();
        exit();
    }else
        ui->labelComentario->setText("La cuota actual no puede ser mayor a la cantidad de cuotas!!!");
}

void CompraEditar::cargarAttributosCompra(){
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

    compra.fechaautorizacion=ui->dateEdit->date().toString("dd-MM-yyyy");
    compra.fechamodificacion=ui->dateEdit->date().toString("dd-MM-yyyy");
    compra.observaciones=ui->lineEditObservaciones->text().simplified();
    compra.terminado="0";
    compra.tipo=ui->comboBox->currentText();
}

void CompraEditar::on_pushButtonCancelar_clicked(){
    exit();
}

void CompraEditar::exit(){
    emit compraEditarTerminado();
    idCompra=INVALIDO;
    this->close();
}

void CompraEditar::load() {
    ui->lineEditPrestador->setText(origNombrePrestador);
    ui->lineEditNumSocio->setText(origIdSocio);
    ui->lineEditSocio->setText(origNombreSocio);
    ui->spinBox->setValue(QString (compra.cantcuotas).toInt());
    ui->spinBoxAct->setValue(QString (compra.cuotaact).toInt());
    ui->checkBoxPrestador->setChecked(true);
    ui->checkBoxNumSocio->setChecked(true);
    ui->checkBoxSocio->setChecked(true);

    QStringList aux = QString(compra.monto).split(".");
    ui->lineEditMonto->setText(aux.at(0));
    if (aux.size() > 1) {
        ui->lineEditMontoDec->setText(aux.at(1));
    }
    ui->dateEdit->setDate(QDate::fromString(compra.fechamodificacion,"dd-MM-yyyy"));
    ui->lineEditObservaciones->setText(compra.observaciones);
    ui->comboBox->setCurrentIndex(ui->comboBox->findText(compra.tipo));
    editado=false;
    ui->pushButtonAgregar->setEnabled(false);
}

void CompraEditar::on_pushButtonDeshacer_clicked()
{
    load();
}
