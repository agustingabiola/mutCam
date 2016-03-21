#ifndef COMPRANUEVO_H
#define COMPRANUEVO_H

#include <QDialog>
#include <QStandardItemModel>

#include "bd.h"
#include "sociobuscar.h"
#include "prestadorbuscar.h"

namespace Ui {class CompraNuevo;}

class CompraNuevo : public QDialog{
    Q_OBJECT
    
public:
    explicit CompraNuevo(QWidget *parent = 0);
    ~CompraNuevo();
    
private slots:
    void todosChequeados();

    void on_lineEditObservaciones_textEdited(const QString &arg1);

    void on_pushButtonSocio_clicked();
    void on_pushButtonPrestador_clicked();

    void on_pushButtonAgregar_clicked();
    void on_pushButtonCancelar_clicked();

private:
    Ui::CompraNuevo *ui;
    PrestadorBuscar *prestadorBuscar;
    SocioBuscar *socioBuscar;

    void conectarCheckBoxes();
    void setLineEditMonto();

    void cargarAttributosCompra();
    void exit();

signals:
    void compraNuevoTerminado();
};

#endif // COMPRANUEVO_H
