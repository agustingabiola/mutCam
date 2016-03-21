#include "prestadornuevo.h"
#include "ui_prestadornuevo.h"

PrestadorNuevo::PrestadorNuevo(QWidget *parent)
                      :QDialog(parent)
                      ,ui(new Ui::PrestadorNuevo){
    ui->setupUi(this);
    idPrestador=INVALIDO;
    conectarCheckBoxes();
    setLineEditCuit();
    setTabOrder(ui->lineEditNombre,ui->lineEditRazonSocial);
    setTabOrder(ui->lineEditRazonSocial,ui->lineEditCuit);
    setTabOrder(ui->lineEditCuit,ui->lineEditDireccion);
    setTabOrder(ui->lineEditDireccion,ui->lineEditEmail);
    setTabOrder(ui->lineEditEmail,ui->lineEditTel);
    setTabOrder(ui->lineEditTel,ui->pushButtonAgregar);
}

PrestadorNuevo::~PrestadorNuevo(){
    delete ui;
}

void PrestadorNuevo::conectarCheckBoxes(){
    connect(ui->checkBoxNombre, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxRazonSocial, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxCuit, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxDomicilio, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxEmail, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxTelefono, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
}

void PrestadorNuevo::todosChequeados(){
    if (ui->checkBoxRazonSocial->isChecked() &&
            ui->checkBoxNombre->isChecked() &&
            ui->checkBoxCuit->isChecked() &&
            ui->checkBoxEmail->isChecked() &&
            ui->checkBoxTelefono->isChecked() &&
            ui->checkBoxDomicilio->isChecked()){
        ui->pushButtonAgregar->setEnabled(true);
    }else
        ui->pushButtonAgregar->setEnabled(false);
}

void  PrestadorNuevo::setLineEditCuit(){
    QRegExp rx("[0-9]{11,11}");
    ui->lineEditCuit->setValidator(new QRegExpValidator(rx, ui->lineEditCuit));
}

void PrestadorNuevo::on_lineEditNombre_textEdited(const QString &arg1){
    QString s=arg1.simplified().toUpper();
    if (!BD::existeNombrePrestador(arg1.toUpper().simplified())){
        if (s.length()<=50 && s.length()>2){
            ui->checkBoxNombre->setEnabled(true);
            ui->checkBoxNombre->setChecked(true);
            ui->labelComentario->setText("");
        }else{
            if (s.length()>3)
                ui->labelComentario->setText("El campo Nombre no puede superar los 50 caracteres");
            else
                ui->labelComentario->setText("El campo Nombre es obligatorio y tiene que tener mas de 3 caracteres");
            ui->checkBoxNombre->setChecked(false);
            ui->checkBoxNombre->setDisabled(true);
        }
    }else{
        ui->labelComentario->setText("El Nombre especificado ya pertenece a otro prestador cargado elija otro");
        ui->checkBoxNombre->setChecked(false);
        ui->checkBoxNombre->setDisabled(true);
    }
}

void PrestadorNuevo::on_lineEditRazonSocial_textEdited(const QString &arg1){
    QString s=arg1.simplified().toUpper();
    if (s.length()<=50 && s.length()>2){
        ui->checkBoxRazonSocial->setEnabled(true);
        ui->checkBoxRazonSocial->setChecked(true);
        ui->labelComentario->setText("");
    }else{
        if (s.length()>50)
            ui->labelComentario->setText("El campo Razón Social no puede superar los 50 caracteres");
        else
            ui->labelComentario->setText("El campo Razón Social es obligatorio y tiene que tener mas de 2 caracteres");
        ui->checkBoxRazonSocial->setChecked(false);
        ui->checkBoxRazonSocial->setDisabled(true);
    }
}

void PrestadorNuevo::on_lineEditCuit_textEdited(const QString &arg1){
    if ((arg1.length()==11 || arg1.isEmpty())){
        ui->checkBoxCuit->setEnabled(true);
        ui->checkBoxCuit->setChecked(true);
        ui->labelComentario->setText("");
    }else{
        ui->labelComentario->setText("El campo Cuit debe tener 11 dígitos");
        ui->checkBoxCuit->setChecked(false);
        ui->checkBoxCuit->setDisabled(true);
    }
}

void PrestadorNuevo::on_lineEditDireccion_textEdited(const QString &arg1){
    QString s=arg1.simplified();
    if (s.length()<=50){
        ui->checkBoxDomicilio->setEnabled(true);
        ui->checkBoxDomicilio->setChecked(true);
        ui->labelComentario->setText("");
    }else{
        ui->labelComentario->setText("El campo Dirección no puede superar los 50 caracteres");
        ui->checkBoxDomicilio->setChecked(false);
        ui->checkBoxDomicilio->setDisabled(true);
    }
}

void PrestadorNuevo::on_lineEditEmail_textEdited(const QString &arg1){
    QString s=arg1.simplified();
    if (s.length()<=50){
        ui->checkBoxEmail->setEnabled(true);
        ui->checkBoxEmail->setChecked(true);
        ui->labelComentario->setText("");
    }else{
        ui->labelComentario->setText("El campo Email no puede superar los 50 caracteres");
        ui->checkBoxEmail->setChecked(false);
        ui->checkBoxEmail->setDisabled(true);
    }
}

void PrestadorNuevo::on_lineEditTel_textEdited(const QString &arg1){
    QString s=arg1.simplified();
    if (s.length()<=50){
        ui->checkBoxTelefono->setEnabled(true);
        ui->checkBoxTelefono->setChecked(true);
        ui->labelComentario->setText("");
    }else{
        ui->labelComentario->setText("El campo Telefono no puede superar los 50 caracteres");
        ui->checkBoxTelefono->setChecked(false);
        ui->checkBoxTelefono->setDisabled(true);
    }
}

void PrestadorNuevo::on_pushButtonAgregar_clicked(){
    setDisabled(true);
    cargarAttributosPrestador();
    BD::agregarPrestador();
    exit();
}

void PrestadorNuevo::cargarAttributosPrestador(){
   prestador.razon_social=ui->lineEditRazonSocial->text().simplified().toUpper();
   prestador.nombre=ui->lineEditNombre->text().simplified().toUpper();
   prestador.cuit=ui->lineEditCuit->text().simplified();
   prestador.direccion=ui->lineEditDireccion->text().simplified();
   prestador.mail=ui->lineEditEmail->text().simplified();
   prestador.telefono=ui->lineEditTel->text().simplified();
}

void PrestadorNuevo::on_pushButtonCancelar_clicked(){
    exit();
}

void PrestadorNuevo::exit(){
    emit prestadorNuevoTerminado();
    idPrestador=INVALIDO;
    this->close();
}
