#include "socioeditar.h"
#include "ui_socioeditar.h"

SocioEditar::SocioEditar(QWidget *parent)
                      :QDialog(parent)
                      ,ui(new Ui::SocioEditar){
    ui->setupUi(this);
    conectarCheckBoxes();
    setLineEditNums();
    load();
    editado=false;
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotEditado()));
    connect(ui->radioButtonClubNo, SIGNAL(toggled(bool)), this, SLOT(slotEditado()));
    connect(ui->radioButtonClubSi, SIGNAL(toggled(bool)), this, SLOT(slotEditado()));
    connect(ui->radioButtonFliaNo, SIGNAL(toggled(bool)), this, SLOT(slotEditado()));
    connect(ui->radioButtonFliaSi, SIGNAL(toggled(bool)), this, SLOT(slotEditado()));
    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(slotEditado()));
}

SocioEditar::~SocioEditar(){
    delete ui;
}

void SocioEditar::slotEditado(){
    ui->pushButtonFlia->setEnabled(ui->radioButtonFliaSi->isChecked());
    editado=true;
    todosChequeados();
}

void SocioEditar::conectarCheckBoxes(){
    connect(ui->checkBoxNombre, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxApellido, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxDni, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxDomicilio, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxEmail, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxTelefono, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxNumSocio, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxEmpresa, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
}

void SocioEditar::todosChequeados(){
    if (ui->checkBoxApellido->isChecked() &&
            ui->checkBoxNombre->isChecked() &&
            ui->checkBoxDni->isChecked() &&
            ui->checkBoxEmail->isChecked() &&
            ui->checkBoxTelefono->isChecked() &&
            ui->checkBoxEmpresa->isChecked() &&
            ui->checkBoxNumSocio->isChecked() &&
            ui->checkBoxDomicilio->isChecked()&&
        editado){
    ui->pushButtonActualizar->setEnabled(true);
}else
    ui->pushButtonActualizar->setEnabled(false);
}

void SocioEditar::setLineEditNums(){
    QRegExp rx1("[0-9]{7,7}");
    ui->lineEditNumSocio->setValidator(new QRegExpValidator(rx1, ui->lineEditNumSocio));
    QRegExp rx2("[0-9]{8,8}");
    ui->lineEditDni->setValidator(new QRegExpValidator(rx2, ui->lineEditDni));
    QRegExp rx3("[0-9]{5,5}");
    ui->lineEditNumSocio->setValidator(new QRegExpValidator(rx3, ui->lineEditNumSocio));
}

void SocioEditar::load(){
    editado=false;
    ui->pushButtonActualizar->setEnabled(false);
    ui->lineEditApellido->setText(socio.apellido);
    ui->lineEditNombre->setText(socio.nombre);
    ui->lineEditNumSocio->setText(idSocio);
    QStringList sl=BD::getEmpresas();
    int index=sl.indexOf(empresa.nombre);
    ui->comboBox->addItems(sl);
    ui->comboBox->setCurrentIndex(index);
    if (socio.grupofamiliar==SI)
        ui->radioButtonFliaSi->setChecked(true);
    else
        ui->radioButtonFliaNo->setChecked(true);
    if (socio.clubporve==SI)
        ui->radioButtonClubSi->setChecked(true);
    else
        ui->radioButtonClubNo->setChecked(true);
    QDate t=QDate::fromString(socio.fechanac,"dd-MM-yyyy");
    ui->dateEdit->setDate(t);
    ui->lineEditDni->setText(socio.dni);
    ui->lineEditDireccion->setText(socio.direccion);
    ui->lineEditTel->setText(socio.telefono);
    ui->lineEditEmail->setText(socio.mail);
    ui->pushButtonFlia->setEnabled(ui->radioButtonFliaSi->isChecked());
}

void SocioEditar::on_lineEditNombre_textEdited(const QString &arg1){
    QString s=arg1.simplified().toUpper();
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
    editado=true;
    todosChequeados();
}

void SocioEditar::on_lineEditApellido_textEdited(const QString &arg1){
    QString s=arg1.simplified().toUpper();
    if (s.length()<=50 && s.length()>2){
        ui->checkBoxApellido->setEnabled(true);
        ui->checkBoxApellido->setChecked(true);
        ui->labelComentario->setText("");
    }else{
        if (s.length()>50)
            ui->labelComentario->setText("El campo Apellido no puede superar los 50 caracteres");
        else
            ui->labelComentario->setText("El campo Apellido es obligatorio y tiene que tener mas de 2 caracteres");
        ui->checkBoxApellido->setChecked(false);
        ui->checkBoxApellido->setDisabled(true);
    }
    editado=true;
    todosChequeados();
}

void SocioEditar::on_lineEditNumSocio_textEdited(const QString &arg1){
    QString nombreyapellido;
    if (arg1.length()==5){
        if (!BD::existeNumSocio(arg1, nombreyapellido) || arg1==idSocio){
            ui->checkBoxNumSocio->setEnabled(true);
            ui->checkBoxNumSocio->setChecked(true);
            ui->labelComentario->setText("");
        }else{
            ui->labelComentario->setText("El #Socio "+ arg1+" pertenece a "+nombreyapellido+" elija otro");
            ui->checkBoxNumSocio->setChecked(false);
            ui->checkBoxNumSocio->setDisabled(true);
        }
    }else{
        ui->labelComentario->setText("El #Socio es obligatorio y tiene que tener 5 digitos");
        ui->checkBoxNumSocio->setChecked(false);
        ui->checkBoxNumSocio->setDisabled(true);
    }
    editado=true;
    todosChequeados();
}

void SocioEditar::on_lineEditDni_textEdited(const QString &arg1){
    if ((arg1.length()<8)){
        ui->labelComentario->setText("El campo D.N.I es obligatorio y debe tener 8 dígitos");
        ui->checkBoxDni->setChecked(false);
        ui->checkBoxDni->setDisabled(true);
    }else{
        ui->checkBoxDni->setEnabled(true);
        ui->checkBoxDni->setChecked(true);
        ui->labelComentario->setText("");
    }
    editado=true;
    todosChequeados();
}

void SocioEditar::on_lineEditDireccion_textEdited(const QString &arg1){
    QString s=arg1.simplified();
    if (s.length()<=50){
        ui->checkBoxDomicilio->setEnabled(true);
        ui->checkBoxDomicilio->setChecked(true);
        ui->labelComentario->setText("");
    }else{
        ui->labelComentario->setText("El campo Domicilio no puede superar los 50 caracteres");
        ui->checkBoxDomicilio->setChecked(false);
        ui->checkBoxDomicilio->setDisabled(true);
    }
    editado=true;
    todosChequeados();
}

void SocioEditar::on_lineEditEmail_textEdited(const QString &arg1){
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

void SocioEditar::on_lineEditTel_textEdited(const QString &arg1){
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

void SocioEditar::on_pushButtonActualizar_clicked(){
    setDisabled(true);
    cargarAttributosSocio();
    BD::actualizarSocio(ui->lineEditNumSocio->text().simplified());
    exit();
}

void SocioEditar::cargarAttributosSocio(){
    socio.nombre=ui->lineEditNombre->text().simplified().toUpper();
    socio.apellido=ui->lineEditApellido->text().simplified().toUpper();
    socio.direccion=ui->lineEditDireccion->text().simplified();
    socio.mail=ui->lineEditEmail->text().simplified();
    socio.telefono=ui->lineEditTel->text().simplified();
    socio.dni=ui->lineEditDni->text().simplified();
    if (ui->radioButtonClubSi->isChecked())
        socio.clubporve=SI;
    else
        socio.clubporve=NO;
    if (ui->radioButtonFliaSi->isChecked())
        socio.grupofamiliar=SI;
    else{
        socio.grupofamiliar=NO;
        socio.flia="";
    }
    BD::cargarIdPorNombre(ui->comboBox->currentText());
    socio.fechanac=ui->dateEdit->date().toString("dd-MM-yyyy");
}

void SocioEditar::on_pushButtonEliminar_clicked(){
    QMessageBox::StandardButton reply;
    reply=QMessageBox::information(this, "Desea Continuar?"
                              , "Si continua se borrara este SOCIO permanentemente. \n"
                                "y ademas se borraran todas las COMPRAS relacionadas con el mismo. \n"
                                "En caso afirmativo se le pedira otra confirmacion"
                              , QMessageBox::Ok|QMessageBox::No);
    if (reply==QMessageBox::Ok){
        reply=QMessageBox::critical(this, "Esta Seguro Que Desea Continuar?"
                                     , "Si continua se borrara este SOCIO permanentemente.  \n"
                                       "y ademas se borraran todas las COMPRAS relacionadas con el mismo. \n"
                                       "Esta accion no se puede deshacer."
                                     , QMessageBox::Ok|QMessageBox::No);
        if (reply==QMessageBox::Ok){
            setDisabled(true);
            BD::eliminarSocio();
            exit();
        }
    }
}

void SocioEditar::on_pushButtonDeshacer_clicked(){
    load();
}

void SocioEditar::on_pushButtonCancelar_clicked(){
    exit();
}

void SocioEditar::on_pushButtonFlia_clicked(){
    gl=new GrupoFlia();
    gl->exec();
    showNormal();
    raise();
    activateWindow();
}

void SocioEditar::exit(){
    emit socioEditarTerminado();
    idSocio=INVALIDO;
    this->close();
}
