#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QSqlQueryModel>



extern const QString NO;
extern const QString SI;
extern QSqlQueryModel *model;
extern const QString INVALIDO;
extern const QString numFlia;
extern const QString numCuota;
extern const QString numPorve;
extern const QString SEPARADOR_TEXTO;



/*******************************  EMPRESAS  *******************************/

struct emp{
    QString razon_social;
    QString cuit;
    QString nombre;
    QString telefono;
    QString direccion;
    QString mail;
};

extern emp empresa;
extern QString idEmpresa;

/*******************************  FIN EMPRESAS  *******************************/



/*******************************  SOCIOS  *******************************/

struct soc{
    QString nombre;
    QString apellido;
    QString dni;
    QString grupofamiliar;
    QString fechanac;
    QString telefono;
    QString direccion;
    QString mail;
    QString clubporve;
    QString flia;
};

extern soc socio;
extern QString idSocio;

/*******************************  FIN SOCIOS  *******************************/



/*******************************  PRESTADORES  *******************************/

struct pre{
    QString razon_social;
    QString cuit;
    QString nombre;
    QString telefono;
    QString direccion;
    QString mail;
};

extern pre prestador;
extern QString idPrestador;

/*******************************  FIN PRESTADORES  *******************************/



/*******************************  COMPRAS  *******************************/

struct com{
    QString monto;
    QString cantcuotas;
    QString cuotaact;
    QString tipo;
    QString fechaautorizacion;
    QString fechamodificacion;
    QString observaciones;
    QString terminado;
};

extern com compra;
extern QString idCompra;

/*******************************  FIN COMPRAS  *******************************/

#endif // GLOBAL_H
