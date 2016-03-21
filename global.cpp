#include "global.h"



const QString NO="NO";
const QString SI="SI";
QSqlQueryModel *model=new QSqlQueryModel();
const QString INVALIDO="0";
extern const QString numCuota="CUOTA CLUB PORVENIR";
extern const QString numFlia="GRUPO FAMILIAR";
extern const QString numPorve="CUOTA SOCIO";
const QString SEPARADOR_TEXTO="$°#";



/*******************************  EMPRESAS  *******************************/

emp empresa={"","","","","",""};
QString idEmpresa=INVALIDO;

/*******************************  FIN EMPRESAS  *******************************/



/*******************************  SOCIOS  *******************************/

soc socio={"","","","","","","","","",""};
QString idSocio=INVALIDO;

/*******************************  FIN SOCIOS  *******************************/



/*******************************  PRESTADORES  *******************************/

pre prestador={"","","","","",""};
QString idPrestador=INVALIDO;

/*******************************  FIN PRESTADORES  *******************************/



/*******************************  COMPRAS  *******************************/

com compra={"","","","","","","",""};
QString idCompra=INVALIDO;

/*******************************  FIN COMPRAS  *******************************/
