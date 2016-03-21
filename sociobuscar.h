#ifndef SOCIOBUSCAR_H
#define SOCIOBUSCAR_H

#include <QDialog>
#include <QtSql>
#include "bd.h"

namespace Ui {class SocioBuscar;}

class SocioBuscar : public QDialog{
    Q_OBJECT
    
public:
    explicit SocioBuscar(QWidget *parent = 0);
    ~SocioBuscar();

private slots:
    void on_lineEditBuscar_textChanged(const QString &arg1);

    void on_pushButtonSeleccionar_clicked();
    void on_pushButtonCancelar_clicked();

private:
    Ui::SocioBuscar *ui;

    void setTableView();

    void keyPressEvent(QKeyEvent * event);
};

#endif // CLIENTEBUSCAR_H
