#ifndef EMPRESABUSCAR_H
#define EMPRESABUSCAR_H

#include <QDialog>
#include <QtSql>
#include "bd.h"
#include "empresanueva.h"

namespace Ui {class EmpresaBuscar;}

class EmpresaBuscar : public QDialog{
    Q_OBJECT
    
public:
    explicit EmpresaBuscar(QWidget *parent = 0);
    ~EmpresaBuscar();

private slots:
    void on_lineEditBuscar_textChanged(const QString &arg1);

    void on_pushButtonNuevoEmpresa_clicked();

    void on_pushButtonSeleccionar_clicked();
    void on_pushButtonEliminar_clicked();
    void on_pushButtonCancelar_clicked();

private:
    Ui::EmpresaBuscar *ui;
    EmpresaNueva *empresaNuevo;

    void setTableView();

    void keyPressEvent(QKeyEvent * event);
};

#endif // CLIENTEBUSCAR_H
