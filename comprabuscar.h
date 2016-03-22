#ifndef COMPRABUSCAR_H
#define COMPRABUSCAR_H

#include <QDialog>
#include <QtSql>
#include "bd.h"
#include "sociobuscar.h"
#include "prestadorbuscar.h"
#include "printbusquedacompras.h"

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

private:
    Ui::CompraBuscar *ui;
    SocioBuscar *searchSocio;
    PrestadorBuscar *searchPrestador;

    bool socioSeleccionado;
    bool prestadorSeleccionado;

    void setTableView();
    void keyPressEvent(QKeyEvent * event);
};

#endif // COMPRABUSCAR_H
