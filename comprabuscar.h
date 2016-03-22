#ifndef COMPRABUSCAR_H
#define COMPRABUSCAR_H

#include <QDialog>
#include <QtSql>
#include "bd.h"
#include "sociobuscar.h"
#include "prestadorbuscar.h"
#include "printbusquedacompras.h"
#include "compraeditar.h"

namespace Ui {class CompraBuscar;}

class CompraBuscar : public QDialog{
    Q_OBJECT
    
public:
    explicit CompraBuscar(QWidget *parent = 0);
    ~CompraBuscar();

private slots:
    void on_pushButtonBuscarPrestador_clicked();
    void on_pushButtonBuscarSocio_clicked();
    void on_pushButtonEliminar_clicked();
    void comboBox();
    void on_pushButtonCancelar_clicked();
    void on_pushButtonImprimir_clicked();
    void editarCompra();
    void repopularModelo();

private:
    Ui::CompraBuscar *ui;
    SocioBuscar *searchSocio;
    PrestadorBuscar *searchPrestador;
    CompraEditar *compraEditar;

    bool socioSeleccionado;
    bool prestadorSeleccionado;

    void setTableView();
    void keyPressEvent(QKeyEvent * event);
    void cargarCompra(int row);
};

#endif // COMPRABUSCAR_H
