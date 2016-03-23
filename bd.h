#ifndef BD_H
#define BD_H

#include <QtSql>
#include <QMessageBox>
#include <QApplication>
#include "global.h"
#include "printcierre.h"
#include "qstringmoney.h"
#include "grupoflia.h"
#include "dialogespera.h"

class BD : public QObject{
    Q_OBJECT

public:
    explicit BD();
    ~BD();

    static void conexion();
    static void crearTablas();
    static void hacerBackUp(QString path);

    static bool agregarEmpresa();
    static void buscarEmpresa(QString busqueda);
    static void actualizarEmpresa();
    static void eliminarEmpresa();
    static bool existenEmpresas();
    static bool existeNombreEmpresa(QString nombre);
    static void cargarIdPorNombre(QString nombre);
    static void cargarEmpresaPorId();
    static QStringList getEmpresas();

    static bool agregarSocio();
    static void buscarSocio(QString busqueda);
    static void actualizarSocio(QString idAux);
    static void eliminarSocio();
    static bool existeNumSocio(QString idSocioAux, QString &nombreyapellido );

    static bool agregarPrestador();
    static void buscarPrestador(QString busqueda);
    static void actualizarPrestador();
    static void eliminarPrestador();
    static bool existeNombrePrestador(QString nombre);
    static void buscarSaldoPrestadores(QString busqueda);

    static bool agregarCompra();
    static void actualizarCompra();
    static void buscarCompra(QString busqueda);
    static void eliminarCompra();

    static void agregarCierre(QString idemp);
    static void printCierreMensual(QString idemp);
    static bool hoySeHizoCierre();

    static void actualizarMonto(QString nombre, QString valor);
    static double obtenerMonto(QString nombre);

private:
    static QSqlDatabase db;
    static QSqlQuery query;
    static QString instruccion;
    static QStringList slidsempresa;
    static DialogEspera *d_espera;
    static int progressIncrement;

    static bool abrir();
    static bool ejecutar(const QString titulo="");

    static void crearTablaEmpresas();
    static void ultimoEmpresaAgregado();

    static void crearTablaSocios();

    static void crearTablaPrestadores();
    static void ultimoPrestadorAgregado();

    static void crearTablaCompras();
    static void ultimoCompraAgregado();

    static void crearTablaMontos();

    static void crearTablaCierres();
};

#endif // BD_H
