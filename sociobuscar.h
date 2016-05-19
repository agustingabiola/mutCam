#ifndef SOCIOBUSCAR_H
#define SOCIOBUSCAR_H

#include <QDialog>
#include <QtSql>
#include "bd.h"
#include "printsociosbusqueda.h"

namespace Ui {class SocioBuscar;}

class SocioBuscar : public QDialog{
    Q_OBJECT
    
public:
    explicit SocioBuscar(QWidget *parent = 0);
    ~SocioBuscar();

private slots:
    void on_lineEditBuscar_textChanged(const QString &arg1);

    void onPushButtonSeleccionar_clicked();
    void on_pushButtonCancelar_clicked();

    void on_pushButtonImprimir_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::SocioBuscar *ui;

    void setTableView();

    void keyPressEvent(QKeyEvent * event);

    void setModelAndHeaders();
};

#endif // CLIENTEBUSCAR_H
