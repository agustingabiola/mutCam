#ifndef COMPRAEDITAR_H
#define COMPRAEDITAR_H

#include <QDialog>
#include <QStandardItemModel>

#include "bd.h"
#include "sociobuscar.h"
#include "prestadorbuscar.h"

namespace Ui {
class CompraEditar;
}

class CompraEditar : public QDialog
{
    Q_OBJECT
    
public:
    explicit CompraEditar(QWidget *parent = 0);
    ~CompraEditar();
    
private slots:
    void todosChequeados();

    void on_lineEditObservaciones_textEdited(const QString &arg1);

    void on_pushButtonSocio_clicked();
    void on_pushButtonPrestador_clicked();

    void on_pushButtonAgregar_clicked();
    void on_pushButtonCancelar_clicked();

    void on_pushButtonDeshacer_clicked();

    void fieldEdited();

private:
    Ui::CompraEditar *ui;
    PrestadorBuscar *prestadorBuscar;
    SocioBuscar *socioBuscar;
    bool editado;
    QString origIdPrestador, origNombrePrestador, origIdSocio, origNombreSocio;

    void conectarCheckBoxes();
    void setLineEditMonto();

    void cargarAttributosCompra();
    void load();
    void exit();

signals:
    void compraEditarTerminado();
};


#endif // COMPRAEDITAR_H
