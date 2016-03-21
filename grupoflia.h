#ifndef GRUPOFLIA_H
#define GRUPOFLIA_H

#include <QDialog>
#include <QStandardItemModel>
#include "bd.h"

namespace Ui {class GrupoFlia;}

class GrupoFlia : public QDialog{
    Q_OBJECT
    
public:
    explicit GrupoFlia(QWidget *parent = 0);
    ~GrupoFlia();
    
private slots:
    void on_pushButtonAceptar_clicked();
    void on_pushButtonEliminar_clicked();
    void on_pushButtonCancelar_clicked();
    void on_pushButtonAgregar_clicked();

private:
    Ui::GrupoFlia *ui;

    void exit();
};

#endif // GRUPOFLIA_H
