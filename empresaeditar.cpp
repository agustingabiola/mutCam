#include "empresaeditar.h"
#include "ui_empresaeditar.h"

EmpresaEditar::EmpresaEditar(QWidget *parent)
                      :QDialog(parent)
                      ,ui(new Ui::EmpresaEditar){
    ui->setupUi(this);
    conectarCheckBoxes();
    setLineEditCuit();
    load();
    editado=false;
}

EmpresaEditar::~EmpresaEditar(){
    delete ui;
}

void EmpresaEditar::conectarCheckBoxes(){
    connect(ui->checkBoxNombre, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxRazonSocial, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxCuit, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxDomicilio, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxEmail, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxTelefono, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
}

void EmpresaEditar::todosChequeados(){
    if (ui->checkBoxRazonSocial->isChecked() &&
            ui->checkBoxNombre->isChecked() &&
            ui->checkBoxCuit->isChecked() &&
            ui->checkBoxEmail->isChecked() &&
            ui->checkBoxTelefono->isChecked() &&
            ui->checkBoxDomicilio->isChecked()&&
            editado){
        ui->pushButtonActualizar->setEnabled(true);
    }else
        ui->pushButtonActualizar->setEnabled(false);
}

void  EmpresaEditar::setLineEditCuit(){
    QRegExp rx("[0-9]{11,11}");
    ui->lineEditCuit->setValidator(new QRegExpValidator(rx, ui->lineEditCuit));
}

void EmpresaEditar::load(){
    editado=false;
    ui->pushButtonActualizar->setEnabled(false);
    ui->lineEditRazonSocial->setText(empresa.razon_social);
    ui->lineEditNombre->setText(empresa.nombre);
    ui->lineEditDireccion->setText(empresa.direccion);
    ui->lineEditCuit->setText(empresa.cuit);
    ui->lineEditTel->setText(empresa.telefono);
    ui->lineEditEmail->setText(empresa.mail);
}

void EmpresaEditar::on_lineEditNombre_textEdited(const QString &arg1){
    QString s=arg1.simplified().toUpper();
    if (!BD::existeNombreEmpresa(arg1.toUpper().simplified())){
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
        ui->labelComentario->setText("El Nombre especificado ya pertenece a otra empresa cargada elija otro");
        ui->checkBoxNombre->setChecked(false);
        ui->checkBoxNombre->setDisabled(true);
    }
    editado=true;
    todosChequeados();
}

void EmpresaEditar::on_lineEditRazonSocial_textEdited(const QString &arg1){
    QString s=arg1.simplified().toUpper();
    if (s.length()<=50 && s.length()>2){
        ui->checkBoxRazonSocial->setEnabled(true);
        ui->checkBoxRazonSocial->setChecked(true);
        ui->labelComentario->setText("");
    }else{
        if (s.length()>50)
            ui->labelComentario->setText("El campo Raz�n Social no puede superar los 50 caracteres");
        else
            ui->labelComentario->setText("El campo Raz�n Social es obligatorio y tiene que tener mas de 2 caracteres");
        ui->checkBoxRazonSocial->setChecked(false);
        ui->checkBoxRazonSocial->setDisabled(true);
    }
    editado=true;
    todosChequeados();
}

void EmpresaEditar::on_lineEditCuit_textEdited(const QString &arg1){
    if ((arg1.length()==11 || arg1.isEmpty())){
        ui->checkBoxCuit->setEnabled(true);
        ui->checkBoxCuit->setChecked(true);
        ui->labelComentario->setText("");
    }else{
        ui->labelComentario->setText("El campo Cuit debe tener 11 d�gitos");
        ui->checkBoxCuit->setChecked(false);
        ui->checkBoxCuit->setDisabled(true);
    }
    editado=true;
    todosChequeados();
}

void EmpresaEditar::on_lineEditDireccion_textEdited(const QString &arg1){
    QString s=arg1.simplified();
    if (s.length()<=50){
        ui->checkBoxDomicilio->setEnabled(true);
        ui->checkBoxDomicilio->setChecked(true);
        ui->labelComentario->setText("");
    }else{
        ui->labelComentario->setText("El campo Direcci�n no puede superar los 50 caracteres");
        ui->checkBoxDomicilio->setChecked(false);
        ui->checkBoxDomicilio->setDisabled(true);
    }
    editado=true;
    todosChequeados();
}

void EmpresaEditar::on_lineEditEmail_textEdited(const QString &arg1){
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
    editado=true;
    todosChequeados();
}

void EmpresaEditar::on_lineEditTel_textEdited(const QString &arg1){
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
    editado=true;
    todosChequeados();
}

void EmpresaEditar::on_pushButtonActualizar_clicked(){
    setDisabled(true);
    cargarAttributosEmpresa();
    BD::actualizarEmpresa();
    exit();
}

void EmpresaEditar::cargarAttributosEmpresa(){
   empresa.razon_social=ui->lineEditRazonSocial->text().simplified().toUpper();
   empresa.nombre=ui->lineEditNombre->text().simplified().toUpper();
   empresa.cuit=ui->lineEditCuit->text().simplified();
   empresa.direccion=ui->lineEditDireccion->text().simplified();
   empresa.mail=ui->lineEditEmail->text().simplified();
   empresa.telefono=ui->lineEditTel->text().simplified();
}

void EmpresaEditar::on_pushButtonEliminar_clicked(){
    QMessageBox::StandardButton reply;
    reply=QMessageBox::information(this, "Desea Continuar?"
                              , "Si continua se borrara esta EMPRESA permanentemente. \n"
                                "y ademas se borraran todos SOCIOS relacionadas con la misma y todas las COMPRAS echas por dichos SOCIOS. \n"
                                "En caso afirmativo se le pedira otra confirmacion"
                              , QMessageBox::Ok|QMessageBox::No);
    if (reply==QMessageBox::Ok){
        reply=QMessageBox::critical(this, "Esta Seguro Que Desea Continuar?"
                                     , "Si continua borrara esta EMPRESA permanentemente \n"
                                       "y ademas se borraran todos SOCIOS relacionadas con la misma y todas las COMPRAS echas por dichos SOCIOS. \n"
                                       "Esta accion no se puede deshacer."
                                     , QMessageBox::Ok|QMessageBox::No);
        if (reply==QMessageBox::Ok){
            setDisabled(true);
            BD::eliminarEmpresa();
            exit();
        }
    }
}

void EmpresaEditar::on_pushButtonDeshacer_clicked(){
    load();
}

void EmpresaEditar::on_pushButtonCancelar_clicked(){
    exit();
}

void EmpresaEditar::exit(){
    emit empresaEditarTerminado();
    idEmpresa=INVALIDO;
    this->close();
}
