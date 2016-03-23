#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include <QInputDialog>

#include "bd.h"

#include "empresanueva.h"
#include "empresabuscar.h"
#include "empresaeditar.h"

#include "socionuevo.h"
#include "sociobuscar.h"
#include "socioeditar.h"

#include "prestadornuevo.h"
#include "prestadorbuscar.h"
#include "prestadoreditar.h"
#include "prestadoressaldos.h"

#include "compranuevo.h"
#include "comprabuscar.h"

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void accionTerminada();
    void on_pushButtonBackUp_clicked();
    void on_pushButtonSalir_clicked();
    void on_pushButtonF1_clicked();
    void on_pushButtonF5_clicked();
    void on_pushButtonF9_clicked();

    void on_actionNueva_Empresa_triggered();
    void on_actionEditar_Empresa_triggered();

    void on_actionNuevo_Socio_triggered();
    void on_actionEditar_Socio_triggered();

    void on_actionNuevo_Prestador_triggered();
    void on_actionEditar_Prestador_triggered();

    void on_actionIngresar_Compra_triggered();
    void on_actionBuscar_Compra_triggered();

    void on_actionEfectuar_Cierre_Mensual_triggered();
    void on_actionVer_Cierres_triggered();

    void on_actionCuota_Socio_triggered();
    void on_actionGrupo_Familiar_triggered();
    void on_actionCuota_Club_Porvenir_triggered();

    void closeEvent(QCloseEvent *event);
    void exit();

    void on_actionEfectuar_Cierre_de_Empresa_triggered();

    void on_actionGenerar_Informe_Para_Empresa_del_ultimo_cierre_mensual_triggered();

    void on_actionConsultar_Saldo_deudor_triggered();

private:
    Ui::MainWindow *ui;

    QStackedWidget *pilaWidgets;

    void inicPilaWidgets();
    void checarSiHayempresas();
    void keyPressEvent(QKeyEvent * event);

    EmpresaNueva *empresaNueva;
    EmpresaBuscar *empresaBuscar;
    EmpresaEditar *empresaEditar;

    SocioNuevo *socioNuevo;
    SocioBuscar *socioBuscar;
    SocioEditar *socioEditar;

    PrestadorNuevo *prestadorNuevo;
    PrestadorBuscar *prestadorBuscar;
    PrestadorEditar *prestadorEditar;
    PrestadoresSaldos *prestadoresSaldos;

    CompraNuevo *compraNuevo;
    CompraBuscar *compraBuscar;
};

#endif // MAINWINDOW_H
