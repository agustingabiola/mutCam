#ifndef PRESTADORBUSCAR_H
#define PRESTADORBUSCAR_H

#include <QDialog>
#include <QtSql>
#include "bd.h"
#include "prestadornuevo.h"
#include "printprestadorbusqueda.h"

namespace Ui {class PrestadorBuscar;}

class PrestadorBuscar : public QDialog{
    Q_OBJECT
    
public:
    explicit PrestadorBuscar(QWidget *parent = 0);
    ~PrestadorBuscar();

private slots:
    void on_lineEditBuscar_textChanged(const QString &arg1);

    void on_pushButtonNuevoPrestador_clicked();

    void onPushButtonSeleccionar_clicked();
    void on_pushButtonEliminar_clicked();
    void on_pushButtonCancelar_clicked();

    void on_pushButtonImprimir_clicked();

private:
    Ui::PrestadorBuscar *ui;
    PrestadorNuevo *prestadorNuevo;

    void setTableView();

    void keyPressEvent(QKeyEvent * event);
};

#endif // PRESTADORBUSCAR_H
