#ifndef PRESTADORESSALDOS_H
#define PRESTADORESSALDOS_H

#include <QDialog>
#include "bd.h"
#include <QKeyEvent>
#include "printsaldoprestadores.h"

namespace Ui {
class PrestadoresSaldos;
}

class PrestadoresSaldos : public QDialog
{
    Q_OBJECT
    
public:
    explicit PrestadoresSaldos(QWidget *parent = 0);
    ~PrestadoresSaldos();
    
private slots:
    void on_pushButtonImprimir_clicked();

    void on_pushButtonCancelar_clicked();

    void on_lineEditBuscar_textChanged(const QString &arg1);

private:
    Ui::PrestadoresSaldos *ui;

    void setTableView();

    void keyPressEvent(QKeyEvent * event);
};

#endif // PRESTADORESSALDOS_H
