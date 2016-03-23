#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
                      :QMainWindow(parent)
                      ,ui(new Ui::MainWindow){
    ui->setupUi(this);
    BD::conexion();
    //BD::crearTablas();
    inicPilaWidgets();
    checarSiHayempresas();
    QMessageBox::information(this, "Recordatorio!"
                         , "Recuerde hacer el back-up diariamente!! \n"
                         , QMessageBox::Ok);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::inicPilaWidgets(){
    pilaWidgets=new QStackedWidget;
    pilaWidgets->addWidget(ui->centralWidget);
    setCentralWidget(pilaWidgets);
    pilaWidgets->setCurrentIndex(0);
}

void MainWindow::checarSiHayempresas(){
    if (!BD::existenEmpresas()){
        QMessageBox::information(this, "CARGAR REGISTRO EMPRESA"
                                  , "Se necesita almenos una empresa cargada para que el sistema funcione correctamete. \n"
                                  , QMessageBox::Ok);
        on_actionNueva_Empresa_triggered();
    }
}

void MainWindow::accionTerminada(){
    pilaWidgets->removeWidget(pilaWidgets->widget(1));
    pilaWidgets->setCurrentIndex(0);
    ui->menuBar->show();
    checarSiHayempresas();
}

void MainWindow::on_pushButtonBackUp_clicked(){
    QString path = QFileDialog::getExistingDirectory(this, tr("Seleccionar   Carpeta"));
    if (path!="")
        BD::hacerBackUp(path);
}

void MainWindow::on_pushButtonSalir_clicked(){
    exit();
}

void MainWindow::closeEvent(QCloseEvent *event){
    Q_UNUSED(event);
    exit();
}

void MainWindow::exit(){
    close();
}

void MainWindow::keyPressEvent(QKeyEvent * event){
    switch (event->key()){
    case Qt::Key_F1 : on_actionIngresar_Compra_triggered(); ;
        break;
    case Qt::Key_F5 : on_actionBuscar_Compra_triggered();
        break;
    case Qt::Key_F9 : on_actionVer_Cierres_triggered();
        break;
    }
}

void MainWindow::on_pushButtonF1_clicked(){
    on_actionIngresar_Compra_triggered(); ;
}

void MainWindow::on_pushButtonF5_clicked(){
    on_actionBuscar_Compra_triggered();
}

void MainWindow::on_pushButtonF9_clicked(){
    ui->menuBar->hide();
    BD::printCierreMensual("-1");
    ui->menuBar->show();
}



/******************************* EMPRESAS *******************************/

void MainWindow::on_actionNueva_Empresa_triggered(){
    ui->menuBar->hide();
    empresaNueva=new EmpresaNueva();
    connect(empresaNueva, SIGNAL(empresaNuevaTerminado()), this, SLOT(accionTerminada()));
    pilaWidgets->addWidget(empresaNueva);
    pilaWidgets->setCurrentIndex(1);
}

void MainWindow::on_actionEditar_Empresa_triggered(){
    ui->menuBar->hide();
    empresaBuscar=new EmpresaBuscar();
    empresaBuscar->exec();
    if (idEmpresa!=INVALIDO){
        empresaEditar=new EmpresaEditar();
        connect(empresaEditar, SIGNAL(empresaEditarTerminado()), this, SLOT(accionTerminada()));
        pilaWidgets->addWidget(empresaEditar);
        pilaWidgets->setCurrentIndex(1);
    }else
        ui->menuBar->show();
    showNormal();
    raise();
    activateWindow();
}

/******************************* FIN EMPRESAS *******************************/



/******************************* SOCIOS *******************************/

void MainWindow::on_actionNuevo_Socio_triggered(){
    ui->menuBar->hide();
    socioNuevo=new SocioNuevo();
    connect(socioNuevo, SIGNAL(socioNuevoTerminado()), this, SLOT(accionTerminada()));
    pilaWidgets->addWidget(socioNuevo);
    pilaWidgets->setCurrentIndex(1);
}

void MainWindow::on_actionEditar_Socio_triggered(){
    ui->menuBar->hide();
    socioBuscar=new SocioBuscar();
    socioBuscar->exec();
    if (idSocio!=INVALIDO){
        socioEditar=new SocioEditar();
        connect(socioEditar, SIGNAL(socioEditarTerminado()), this, SLOT(accionTerminada()));
        pilaWidgets->addWidget(socioEditar);
        pilaWidgets->setCurrentIndex(1);
    }else
        ui->menuBar->show();
    showNormal();
    raise();
    activateWindow();
}

/******************************* FIN SOCIOS *******************************/



/******************************* PRESTADORES *******************************/

void MainWindow::on_actionNuevo_Prestador_triggered(){
    ui->menuBar->hide();
    prestadorNuevo=new PrestadorNuevo();
    connect(prestadorNuevo, SIGNAL(prestadorNuevoTerminado()), this, SLOT(accionTerminada()));
    pilaWidgets->addWidget(prestadorNuevo);
    pilaWidgets->setCurrentIndex(1);
}

void MainWindow::on_actionEditar_Prestador_triggered(){
    ui->menuBar->hide();
    prestadorBuscar=new PrestadorBuscar();
    prestadorBuscar->exec();
    if (idPrestador!=INVALIDO){
        prestadorEditar=new PrestadorEditar();
        connect(prestadorEditar, SIGNAL(prestadorEditarTerminado()), this, SLOT(accionTerminada()));
        pilaWidgets->addWidget(prestadorEditar);
        pilaWidgets->setCurrentIndex(1);
        showNormal();
        raise();
        activateWindow();
    }else
        ui->menuBar->show();
}

/******************************* FIN PRESTADORES *******************************/



/******************************* COMPRAS *******************************/

void MainWindow::on_actionIngresar_Compra_triggered(){
    if (BD::hoySeHizoCierre()){
        QMessageBox::information(this, "Cierre Mensual!"
                             , "En el dia de hoy se hizo el cierre mensual, por lo tanto no se podran ingresar mas compras! \n"
                             , QMessageBox::Ok);
    }else{
        ui->menuBar->hide();
        compraNuevo=new CompraNuevo();
        connect(compraNuevo, SIGNAL(compraNuevoTerminado()), this, SLOT(accionTerminada()));
        pilaWidgets->addWidget(compraNuevo);
        pilaWidgets->setCurrentIndex(1);
    }
}

void MainWindow::on_actionBuscar_Compra_triggered(){
    ui->menuBar->hide();
    compraBuscar=new CompraBuscar();
    compraBuscar->exec();
    showNormal();
    raise();
    activateWindow();
    ui->menuBar->show();
}

void MainWindow::on_actionConsultar_Saldo_deudor_triggered()
{
    ui->menuBar->hide();
    prestadoresSaldos = new PrestadoresSaldos();
    prestadoresSaldos->exec();
    showNormal();
    raise();
    activateWindow();
    ui->menuBar->show();
}

/******************************* FIN PRESTADORES *******************************/



/******************************* CIERRES *******************************/

void MainWindow::on_actionEfectuar_Cierre_Mensual_triggered(){
    ui->menuBar->hide();
    BD::agregarCierre("-1");
    ui->menuBar->show();
}

void MainWindow::on_actionVer_Cierres_triggered(){
    ui->menuBar->hide();
    BD::printCierreMensual("-1");
    ui->menuBar->show();
}


void MainWindow::on_actionEfectuar_Cierre_de_Empresa_triggered()
{
    ui->menuBar->hide();
    empresaBuscar=new EmpresaBuscar();
    empresaBuscar->exec();
    if (idEmpresa!=INVALIDO){
        BD::agregarCierre(idEmpresa);
    }
    ui->menuBar->show();
    showNormal();
    raise();
    activateWindow();
}

void MainWindow::on_actionGenerar_Informe_Para_Empresa_del_ultimo_cierre_mensual_triggered()
{
    ui->menuBar->hide();
    empresaBuscar=new EmpresaBuscar();
    empresaBuscar->exec();
    if (idEmpresa!=INVALIDO){
        BD::printCierreMensual(idEmpresa);
    }
    ui->menuBar->show();
    showNormal();
    raise();
    activateWindow();
}

/******************************* FIN CIERRES *******************************/



/******************************* MONTOS *******************************/

void MainWindow::on_actionCuota_Socio_triggered(){
    ui->menuBar->hide();
    bool ok=false;
    double v=BD::obtenerMonto(numCuota);
    double d=QInputDialog::getDouble(this, "Nuevo Importe", numCuota+" :", v, 0, 9999.99, 2, &ok, this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    if (ok){
        BD::actualizarMonto(numCuota,QString::number(d));
    }
    ui->menuBar->show();
}

void MainWindow::on_actionGrupo_Familiar_triggered(){
    ui->menuBar->hide();
    bool ok=false;
    double v=BD::obtenerMonto(numFlia);
    double d=QInputDialog::getDouble(this, "Nuevo Importe", numFlia+" :", v, 0, 9999.99, 2, &ok, this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    if (ok){
        BD::actualizarMonto(numFlia,QString::number(d));
    }
    ui->menuBar->show();
}

void MainWindow::on_actionCuota_Club_Porvenir_triggered(){
    ui->menuBar->hide();
    bool ok=false;
    double v=BD::obtenerMonto(numPorve);
    double d=QInputDialog::getDouble(this, "Nuevo Importe", numPorve+" :", v, 0, 9999.99, 2, &ok, this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    if (ok){
        BD::actualizarMonto(numPorve,QString::number(d));
    }
    ui->menuBar->show();
}

/******************************* FIN MONTOS *******************************/
