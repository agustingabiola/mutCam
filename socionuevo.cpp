#include "socionuevo.h"
#include "ui_socionuevo.h"

SocioNuevo::SocioNuevo(QWidget *parent)
                      :QDialog(parent)
                      ,ui(new Ui::SocioNuevo){
    ui->setupUi(this);
    idSocio=INVALIDO;
    conectarCheckBoxes();
    setLineEditNums();
    ui->comboBox->addItems(BD::getEmpresas());
    socio.flia="";
    connect(ui->radioButtonFliaNo, SIGNAL(toggled(bool)), this, SLOT(slotBoton()));
    connect(ui->radioButtonFliaSi, SIGNAL(toggled(bool)), this, SLOT(slotBoton()));
    setTabOrder(ui->lineEditNombre,ui->lineEditApellido);
    setTabOrder(ui->lineEditApellido,ui->lineEditNumSocio);
    setTabOrder(ui->lineEditNumSocio,ui->radioButtonClubSi);
    setTabOrder(ui->radioButtonClubSi,ui->radioButtonClubNo);
    setTabOrder(ui->radioButtonClubNo,ui->comboBox);
    setTabOrder(ui->comboBox,ui->lineEditDni);
    setTabOrder(ui->lineEditDni,ui->dateEdit);
    setTabOrder(ui->dateEdit,ui->lineEditDireccion);
    setTabOrder(ui->lineEditDireccion,ui->lineEditEmail);
    setTabOrder(ui->lineEditEmail,ui->lineEditTel);
    setTabOrder(ui->lineEditTel,ui->radioButtonFliaSi);
    setTabOrder(ui->radioButtonFliaSi,ui->radioButtonFliaNo);
    setTabOrder(ui->radioButtonFliaNo,ui->pushButtonFlia);
    setTabOrder(ui->pushButtonFlia,ui->pushButtonAgregar);
}

SocioNuevo::~SocioNuevo(){
    delete ui;
}

void SocioNuevo::slotBoton(){
    ui->pushButtonFlia->setEnabled(ui->radioButtonFliaSi->isChecked());
}

void SocioNuevo::conectarCheckBoxes(){
    connect(ui->checkBoxNombre, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxApellido, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxDni, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxDomicilio, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxEmail, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxTelefono, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxNumSocio, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
    connect(ui->checkBoxEmpresa, SIGNAL(stateChanged(int)), this, SLOT(todosChequeados()));
}

void SocioNuevo::todosChequeados(){
    if (ui->checkBoxApellido->isChecked() &&
            ui->checkBoxNombre->isChecked() &&
            ui->checkBoxDni->isChecked() &&
            ui->checkBoxEmail->isChecked() &&
            ui->checkBoxTelefono->isChecked() &&
            ui->checkBoxEmpresa->isChecked() &&
            ui->checkBoxNumSocio->isChecked() &&
            ui->checkBoxDomicilio->isChecked()){
        ui->pushButtonAgregar->setEnabled(true);
    }else
        ui->pushButtonAgregar->setEnabled(false);
}

void SocioNuevo::setLineEditNums(){
    QRegExp rx1("[0-9]{7,7}");
    ui->lineEditNumSocio->setValidator(new QRegExpValidator(rx1, ui->lineEditNumSocio));
    QRegExp rx2("[0-9]{8,8}");
    ui->lineEditDni->setValidator(new QRegExpValidator(rx2, ui->lineEditDni));
    QRegExp rx3("[0-9]{5,5}");
    ui->lineEditNumSocio->setValidator(new QRegExpValidator(rx3, ui->lineEditNumSocio));
}

void SocioNuevo::on_lineEditNombre_textEdited(const QString &arg1){
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
}

void SocioNuevo::on_lineEditApellido_textEdited(const QString &arg1){
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
}

void SocioNuevo::on_lineEditNumSocio_textEdited(const QString &arg1){
    QString nombreyapellido;
    if (arg1.length()==5){
        if (!BD::existeNumSocio(arg1, nombreyapellido)){
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
}

void SocioNuevo::on_lineEditDni_textEdited(const QString &arg1){
    if ((arg1.length()<8)){
        ui->labelComentario->setText("El campo D.N.I es obligatorio y debe tener 8 dígitos");
        ui->checkBoxDni->setChecked(false);
        ui->checkBoxDni->setDisabled(true);
    }else{
        ui->checkBoxDni->setEnabled(true);
        ui->checkBoxDni->setChecked(true);
        ui->labelComentario->setText("");
    }
}

void SocioNuevo::on_lineEditDireccion_textEdited(const QString &arg1){
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
}

void SocioNuevo::on_lineEditEmail_textEdited(const QString &arg1){
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

void SocioNuevo::on_lineEditTel_textEdited(const QString &arg1){
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

void SocioNuevo::on_pushButtonAgregar_clicked(){
    setDisabled(true);
    cargarAttributosSocio();
    BD::agregarSocio();
    exit();
}

void SocioNuevo::cargarAttributosSocio(){
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
    idSocio=ui->lineEditNumSocio->text().simplified();
}

void SocioNuevo::on_pushButtonCancelar_clicked(){
    exit();
}

void SocioNuevo::on_pushButtonFlia_clicked(){
    gl=new GrupoFlia();
    gl->exec();
    showNormal();
    raise();
    activateWindow();
}

void SocioNuevo::exit(){
    emit socioNuevoTerminado();
    idSocio=INVALIDO;
    this->close();
}
