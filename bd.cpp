#include "bd.h"
#include <QFileDialog>
#include <QPrintDialog>

QSqlDatabase BD::db=QSqlDatabase();
QSqlQuery BD::query=QSqlQuery();
QString BD::instruccion="";
QStringList BD::slidsempresa=QStringList();
DialogEspera* BD::d_espera;
int BD::progressIncrement;

BD::BD(){
    BD::query.prepare("ALTER SESSION SET NLS_TERRITORY= 'AMERICA' ");
    ejecutar();
}

BD::~BD(){
}

void BD::conexion(){
    BD::db=QSqlDatabase::addDatabase("QOCI", "app_BD::db");
    BD::query=QSqlQuery(BD::db);
    BD::db.setDatabaseName("XE");
    BD::db.setUserName("admin");
    BD::db.setPassword("killkpo");
    BD::db.setHostName("127.0.0.1");
    BD::db.setPort(1521);
    abrir();
}

bool BD::abrir(){
    bool b=BD::db.open();
    GrupoFlia *gf= new GrupoFlia();
    if (!b){
        QMessageBox::critical(gf,qApp->tr("No Se Puede Abrir Base De Datos"),
                                qApp->tr("No se pudo establecer una conexión.\n"
                                         "Comuniquese con Santiago Pinczinger.\n"
                                         "Envié un email a jpincz@gmail.com con información de contacto.\n"
                                         "Click en OK para salir."), QMessageBox::Ok);
    }
    return b;
}  

bool BD::ejecutar(QString titulo){
    bool b=BD::query.exec() && BD::db.isOpen();
    GrupoFlia *gf= new GrupoFlia();
    if (!b){
        if (titulo!="")
            QMessageBox::critical(gf,"No Se Pudo "+titulo
                                   ,"Comuniquese con Santiago Pinczinger.\n"
                                    "Envié un email a jpincz@gmail.com con información de contacto.\n"
                                    "Adjunte este error al email:\n"
                                    "          "+BD::query.lastError().text()+"\n\n"
                                    "Click OK para continuar.", QMessageBox::Ok);
        else
            QMessageBox::critical(gf,"OPA! Algo Salio Mal!"
                                   ,"Comuniquese con Santiago Pinczinger.\n"
                                    "Envié un email a jpincz@gmail.com con información de contacto.\n"
                                    "Adjunte este error al email:\n"
                                    "          "+BD::query.lastError().text()+"\n\n"
                                    "Click OK para continuar.", QMessageBox::Ok);

    }else
        if (titulo!="")
            QMessageBox::information(gf,QString(titulo)
                                  ,QString("Operación realizada con éxito!."));
    return b;
}

void BD::crearTablas(){
    if (abrir()){
        crearTablaEmpresas();
        crearTablaSocios();
        crearTablaPrestadores();
        crearTablaCompras();
        crearTablaCierres();
        crearTablaMontos();
    }
}

void BD::hacerBackUp(QString path){
    QString date=QDate::currentDate().toString("dd-MM-yy");
    QDir dir(path+"/BACK-UP/"+date);
    if (!dir.exists())
        dir.mkpath(".");

    QFile empresas(path+"/BACK-UP/"+date+"/empresas.txt");
    empresas.open (QIODevice::ReadWrite | QIODevice::Text);
    QTextStream linea_empresa(&empresas);
    query.prepare      ("SELECT idempresa, razon_social, cuit, nombre, telefono, direccion, mail, activado FROM EMPRESAS ORDER BY (idempresa)  ");
    ejecutar();
    while (query.next()) {
        instruccion="";
        instruccion="INSERT INTO EMPRESAS (razon_social, cuit, nombre, telefono, direccion, mail, activado)";
        instruccion.append(" VALUES (");
        instruccion.append("  '"+query.value(1).toString()+"'");
        instruccion.append(", '"+query.value(2).toString()+"'");
        instruccion.append(", '"+query.value(3).toString()+"'");
        instruccion.append(", '"+query.value(4).toString()+"'");
        instruccion.append(", '"+query.value(5).toString()+"'");
        instruccion.append(", '"+query.value(6).toString()+"'");
        instruccion.append(", "+query.value(7).toString());
        instruccion.append(" ) ; ");
        linea_empresa << instruccion << endl << '/' <<endl;
        instruccion.clear ();
    }
    empresas.close ();

    QFile socios(path+"/BACK-UP/"+date+"/socios.txt");
    socios.open (QIODevice::ReadWrite | QIODevice::Text);
    QTextStream linea_socio(&socios);
    query.prepare               ("SELECT idsocio, nombre, apellido, idempresa, grupofamiliar, clubporve, telefono, direccion, mail, dni, fechanac, flia, activado FROM SOCIOS ORDER BY (idsocio)  ");
    ejecutar();
    while (query.next()) {
        instruccion="";
        instruccion="INSERT INTO SOCIOS (idsocio, nombre, apellido, idempresa, grupofamiliar, clubporve, telefono, direccion, mail, dni, fechanac, flia, activado)";
        instruccion.append(" VALUES (");
        instruccion.append("  '"+query.value(0).toString()+"'");
        instruccion.append(", '"+query.value(1).toString()+"'");
        instruccion.append(", '"+query.value(2).toString()+"'");
        instruccion.append(", '"+query.value(3).toString()+"'");
        instruccion.append(", '"+query.value(4).toString()+"'");
        instruccion.append(", '"+query.value(5).toString()+"'");
        instruccion.append(", '"+query.value(6).toString()+"'");
        instruccion.append(", '"+query.value(7).toString()+"'");
        instruccion.append(", '"+query.value(8).toString()+"'");
        instruccion.append(", '"+query.value(9).toString()+"'");
        instruccion.append(", '"+query.value(10).toString()+"'");
        instruccion.append(", '"+query.value(11).toString()+"'");
        instruccion.append(", "+query.value(12).toString());
        instruccion.append(" ) ; ");
        linea_socio << instruccion << endl << '/' <<endl;
        instruccion.clear ();
    }
    socios.close ();

    QFile prestadores(path+"/BACK-UP/"+date+"/prestadores.txt");
    prestadores.open (QIODevice::ReadWrite | QIODevice::Text);
    QTextStream linea_prestador(&prestadores);
    query.prepare       ("SELECT idprestador, razon_social, cuit, nombre, telefono, direccion, mail, activado FROM PRESTADORES ORDER BY (idprestador)  ");
    ejecutar();
    while (query.next()) {
        instruccion="";
        instruccion="INSERT INTO PRESTADORES (razon_social, cuit, nombre, telefono, direccion, mail, activado)";
        instruccion.append(" VALUES (");
        instruccion.append("  '"+query.value(1).toString()+"'");
        instruccion.append(", '"+query.value(2).toString()+"'");
        instruccion.append(", '"+query.value(3).toString()+"'");
        instruccion.append(", '"+query.value(4).toString()+"'");
        instruccion.append(", '"+query.value(5).toString()+"'");
        instruccion.append(", '"+query.value(6).toString()+"'");
        instruccion.append(", "+query.value(7).toString());
        instruccion.append(" ); ");
        linea_prestador << instruccion << endl << '/' <<endl;
        instruccion.clear ();
    }
    prestadores.close ();

    QFile compras(path+"/BACK-UP/"+date+"/compras.txt");
    compras.open (QIODevice::ReadWrite | QIODevice::Text);
    QTextStream linea_compra(&compras);
    query.prepare      ("SELECT idcompra, idsocio, idprestador, monto, cantcuota, cuotaact, tipo, observaciones, terminado, TO_CHAR(fechaautorizacion, 'dd-MM-yyyy'), TO_CHAR(fechamodificacion, 'dd-MM-yyyy'), activado FROM COMPRAS ORDER BY (idcompra)  ");
    ejecutar();
    while (query.next()) {
        instruccion="";
        instruccion="INSERT INTO COMPRAS (idsocio, idprestador, monto, cantcuota, cuotaact, tipo, observaciones, terminado, fechamodificacion, fechaautorizacion, activado) ";
        instruccion.append(" VALUES (");
        instruccion.append("  '"+query.value(1).toString()+"'");
        instruccion.append(", '"+query.value(2).toString()+"'");
        instruccion.append(",  "+query.value(3).toString());
        instruccion.append(",  "+query.value(4).toString());
        instruccion.append(",  "+query.value(5).toString());
        instruccion.append(", '"+query.value(6).toString()+"'");
        instruccion.append(", '"+query.value(7).toString()+"'");
        instruccion.append(",  "+query.value(8).toString());
        instruccion.append(", TO_DATE('"+query.value(9).toString()+"','dd-MM-yyyy')");
        instruccion.append(", TO_DATE('"+query.value(10).toString()+"','dd-MM-yyyy')");
        instruccion.append(",  "+query.value(11).toString());
        instruccion.append(" ) ; ");
        linea_compra << instruccion << endl << '/' <<endl;
        instruccion.clear ();
    }
    compras.close ();

    QFile cierres(path+"/BACK-UP/"+date+"/cierres.txt");
    cierres.open (QIODevice::ReadWrite | QIODevice::Text);
    QTextStream linea_cierre(&cierres);
    query.prepare("SELECT c.* FROM cierres c INNER JOIN (SELECT idempresa, MAX(fechafinal) AS maxDate FROM cierres GROUP BY idempresa) cierresMax ON c.idempresa = cierresMax.idempresa AND c.fechafinal = cierresMax.maxDate");
    ejecutar();
    while (query.next()) {
        QString fecha_actualizacion = query.value(0).toDate().toString("dd-MM-yyyy");
        instruccion="INSERT INTO CIERRES (fechainicio, fechafinal, idempresa) VALUES (TO_DATE('"+fecha_actualizacion+"','dd-MM-yyyy'), TO_DATE('"+fecha_actualizacion+"','dd-MM-yyyy')," + query.value(2).toString() +"); ";
        linea_cierre << instruccion << endl << '/' <<endl;
        instruccion.clear();
    }
    cierres.close ();
    GrupoFlia *gf= new GrupoFlia();
    QMessageBox::information(gf,"BACK UP",QString("Operación realizada con éxito!."));
}



/*******************************  EMPRESAS  *******************************/

void BD::crearTablaEmpresas(){
    instruccion="CREATE TABLE EMPRESAS ( "
                      "idempresa         VARCHAR2(10) NOT NULL, "
                      "razon_social      VARCHAR2(50) NOT NULL, "
                      "cuit              VARCHAR2(11), "
                      "nombre            VARCHAR2(50) NOT NULL, "
                      "telefono          VARCHAR2(50), "
                      "direccion         VARCHAR2(50), "
                      "mail              VARCHAR2(50), "
                      "activado          NUMBER(1,0) DEFAULT 1 NOT NULL, "
                   "constraint        EMPRESAS_PK primary key (idempresa) "
                   ") ";
    BD::query.prepare(instruccion);
    if (ejecutar("Crear Tabla Empresas")){
        instruccion = "CREATE SEQUENCE secuencia_empresas START WITH 1 INCREMENT BY 1 NOCACHE NOCYCLE ";
        BD::query.prepare(instruccion);
        ejecutar("Crear Secuencia de Empresas");
        instruccion = "CREATE OR REPLACE TRIGGER trigger_pk_empresas BEFORE INSERT ON EMPRESAS FOR EACH ROW "
                        "BEGIN "
                            ":new.idempresa := TO_CHAR(secuencia_empresas.nextval); "
                        "END; ";
        BD::query.prepare(instruccion);
        ejecutar("Crear Trigger Key de Empresas");
    }
}

bool BD::agregarEmpresa(){
    instruccion="INSERT INTO EMPRESAS (razon_social, cuit, nombre, telefono, direccion, mail)";
    instruccion.append(" VALUES (");
    instruccion.append("  '"+empresa.razon_social+"'");
    instruccion.append(", '"+empresa.cuit+"'");
    instruccion.append(", '"+empresa.nombre+"'");
    instruccion.append(", '"+empresa.telefono+"'");
    instruccion.append(", '"+empresa.direccion+"'");
    instruccion.append(", '"+empresa.mail+"'");
    instruccion.append(") ");
    BD::query.prepare(instruccion);
    bool b=ejecutar("Agregar Empresa");
    ultimoEmpresaAgregado();
    return b;
}

void BD::buscarEmpresa(QString busqueda){
    model->clear();
    abrir();
    model->setQuery("SELECT idempresa, nombre, razon_social, telefono, mail, cuit, direccion "
                    " FROM EMPRESAS "+busqueda+" ORDER BY (nombre)", BD::db);
}

void BD::actualizarEmpresa(){
    instruccion="UPDATE EMPRESAS SET ";
    instruccion.append("  razon_social='"+empresa.razon_social+"'");
    instruccion.append(", cuit='"+empresa.cuit+"'");
    instruccion.append(", nombre='"+empresa.nombre+"'");
    instruccion.append(", telefono='"+empresa.telefono+"'");
    instruccion.append(", direccion='"+empresa.direccion+"'");
    instruccion.append(", mail='"+empresa.mail+"'");
    instruccion.append(" WHERE idempresa='"+idEmpresa+"'");
    BD::query.prepare(instruccion);
    ejecutar("Actualizar Empresa");
}

void BD::eliminarEmpresa(){
    BD::query.prepare("SELECT idsocio FROM SOCIOS WHERE idempresa='"+idEmpresa+"'");
    ejecutar("Eliminar Socios de Empresa y sus Compras");
    while (BD::query.next()){
        idSocio=query.value(0).toString();
        BD::query.prepare("DELETE FROM SOCIOS WHERE idsocio='"+idSocio+"'");
        ejecutar();
        BD::query.prepare("DELETE FROM COMPRAS WHERE idsocio='"+idSocio+"'");
        ejecutar();
    }
    BD::query.prepare("DELETE FROM EMPRESAS WHERE idempresa='"+idEmpresa+"'");
    ejecutar("Eliminar Empresa");
}

void BD::ultimoEmpresaAgregado(){
    BD::query.prepare("SELECT secuencia_empresas.NEXTVAL FROM DUAL");
    ejecutar();
    BD::query.prepare("SELECT secuencia_empresas.CURRVAL FROM DUAL");
    ejecutar();
    BD::query.prepare("ALTER SEQUENCE secuencia_empresas INCREMENT BY -1");
    ejecutar();
    BD::query.prepare("SELECT secuencia_empresas.NEXTVAL FROM DUAL");
    ejecutar();
    BD::query.prepare("SELECT secuencia_empresas.CURRVAL FROM DUAL");
    ejecutar();
    BD::query.next();
    idEmpresa=BD::query.value(0).toString();
    BD::query.prepare("ALTER SEQUENCE secuencia_empresas INCREMENT BY 1");
    ejecutar();
}

bool BD::existenEmpresas(){
    BD::query.prepare("SELECT COUNT(*) FROM EMPRESAS WHERE activado=1");
    ejecutar();
    BD::query.next();
    return (0<BD::query.value(0).toInt());
}

bool BD::existeNombreEmpresa(QString nombre){
    BD::query.prepare("SELECT COUNT(*) FROM EMPRESAS WHERE nombre='"+nombre+"' AND activado=1");
    ejecutar();
    BD::query.next();
    bool b=0!=BD::query.value(0).toInt();
    return b;
}

void BD::cargarIdPorNombre(QString nombre){
    BD::query.prepare("SELECT idempresa FROM EMPRESAS WHERE nombre='"+nombre+"' AND activado=1");
    ejecutar();
    if (BD::query.next())
        idEmpresa=BD::query.value(0).toString();
    else
        idEmpresa=INVALIDO;
}

void BD::cargarEmpresaPorId(){
    BD::query.prepare("SELECT nombre, razon_social, cuit, telefono, direccion, mail FROM EMPRESAS WHERE idempresa='"+idEmpresa+"' AND activado=1");
    ejecutar();
    BD::query.next();
    empresa.nombre=BD::query.value(0).toString();
    empresa.razon_social=BD::query.value(1).toString();
    empresa.cuit=BD::query.value(2).toString();
    empresa.telefono=BD::query.value(3).toString();
    empresa.direccion=BD::query.value(4).toString();
    empresa.mail=BD::query.value(5).toString();
}

QStringList BD::getEmpresas(){
    QStringList sl;
    BD::query.prepare("SELECT DISTINCT nombre FROM EMPRESAS WHERE activado=1 ORDER BY (nombre)");
    if (ejecutar())
        while (BD::query.next())
            sl.append(BD::query.value(0).toString());
    return sl;
}

/*******************************  FIN EMPRESAS  *******************************/



/*******************************  SOCIOS  *******************************/

void BD::crearTablaSocios(){
    instruccion="CREATE TABLE SOCIOS ( "
                      "idsocio           VARCHAR2(10) NOT NULL, "
                      "nombre            VARCHAR2(50) NOT NULL, "
                      "apellido          VARCHAR2(50) NOT NULL, "
                      "idempresa         VARCHAR2(10) NOT NULL, "
                      "dni               VARCHAR2(8) NOT NULL, "
                      "grupofamiliar     VARCHAR2(2) NOT NULL, "
                      "clubporve         VARCHAR2(2) NOT NULL, "
                      "fechanac          VARCHAR2(20) NOT NULL, "
                      "telefono          VARCHAR2(50), "
                      "direccion         VARCHAR2(50), "
                      "mail              VARCHAR2(50), "                      
                      "activado          NUMBER(1,0) DEFAULT 1 NOT NULL, "
                      "flia              CLOB, "
                   "constraint        SOCIOS_PK primary key (idsocio) "
                   ") ";
    BD::query.prepare(instruccion);
    ejecutar("Crear Tabla Socios");
}

bool BD::agregarSocio(){
    instruccion="INSERT INTO SOCIOS (idsocio, nombre, apellido, idempresa, grupofamiliar, clubporve, telefono, direccion, mail, dni, fechanac, flia)";
    instruccion.append(" VALUES (");
    instruccion.append("  '"+idSocio+"'");
    instruccion.append(", '"+socio.nombre+"'");
    instruccion.append(", '"+socio.apellido+"'");
    instruccion.append(", '"+idEmpresa+"'");
    instruccion.append(", '"+socio.grupofamiliar+"'");
    instruccion.append(", '"+socio.clubporve+"'");
    instruccion.append(", '"+socio.telefono+"'");
    instruccion.append(", '"+socio.direccion+"'");
    instruccion.append(", '"+socio.mail+"'");
    instruccion.append(", '"+socio.dni+"'");
    instruccion.append(", '"+socio.fechanac+"'");
    instruccion.append(", '"+socio.flia+"'");
    instruccion.append(") ");
    BD::query.prepare(instruccion);
    bool b=ejecutar("Agregar Socio");
    return b;
}

void BD::buscarSocio(QString busqueda){
    model->clear();
    abrir();
    model->setQuery("SELECT socios.idsocio, socios.nombre, socios.apellido, empresas.nombre, socios.grupofamiliar, socios.clubporve, socios.telefono, socios.direccion, socios.mail, socios.dni, socios.fechanac, socios.flia "
                    " FROM SOCIOS JOIN EMPRESAS ON empresas.idempresa = socios.idempresa "+busqueda, BD::db);
}

void BD::actualizarSocio(QString idAux){
    instruccion="UPDATE SOCIOS SET ";
    instruccion.append("  idsocio='"+idAux+"'");
    instruccion.append(", nombre='"+socio.nombre+"'");
    instruccion.append(", apellido='"+socio.apellido+"'");
    instruccion.append(", idempresa='"+idEmpresa+"'");
    instruccion.append(", grupofamiliar='"+socio.grupofamiliar+"'");
    instruccion.append(", clubporve='"+socio.clubporve+"'");
    instruccion.append(", direccion='"+socio.direccion+"'");
    instruccion.append(", dni='"+socio.dni+"'");
    instruccion.append(", fechanac='"+socio.fechanac+"'");
    instruccion.append(", telefono='"+socio.telefono+"'");
    instruccion.append(", mail='"+socio.mail+"'");
    instruccion.append(", flia='"+socio.flia+"'");
    instruccion.append(" WHERE idsocio='"+idSocio+"'");
    BD::query.prepare(instruccion);
    ejecutar("Actualizar Socio");
}

void BD::eliminarSocio(){
    BD::query.prepare("DELETE FROM SOCIOS WHERE idsocio='"+idSocio+"'");
    ejecutar("Eliminar Socio");
    BD::query.prepare("DELETE FROM COMPRAS WHERE idsocio='"+idSocio+"'");
    ejecutar("Eliminar Compras de Socio");
}

bool BD::existeNumSocio(QString idSocioAux, QString &nombreyapellido){
    BD::query.prepare("SELECT COUNT(*) FROM SOCIOS WHERE idsocio='"+idSocioAux+"' AND activado=1");
    ejecutar();
    BD::query.next();
    bool b=0!=BD::query.value(0).toInt();
    if (b){
        BD::query.prepare("SELECT nombre, apellido FROM SOCIOS WHERE idsocio='"+idSocioAux+"'");
        ejecutar();
        BD::query.next();
        nombreyapellido=BD::query.value(0).toString()+" "+BD::query.value(1).toString();
    }
    return b;
}

/*******************************  FIN SOCIOS  *******************************/



/*******************************  PRESTADORES  *******************************/

void BD::crearTablaPrestadores(){
    instruccion="CREATE TABLE PRESTADORES ( "
                      "idprestador       VARCHAR2(10) NOT NULL, "
                      "razon_social      VARCHAR2(50) NOT NULL, "
                      "cuit              VARCHAR2(11), "
                      "nombre            VARCHAR2(50) NOT NULL, "
                      "telefono          VARCHAR2(50), "
                      "direccion         VARCHAR2(50), "
                      "mail              VARCHAR2(50), "
                      "activado          NUMBER(1,0) DEFAULT 1 NOT NULL, "
                   "constraint        PRESTADORES_PK primary key (idprestador) "
                   ") ";
    BD::query.prepare(instruccion);
    if (ejecutar("Crear Tabla Prestadores")){
        instruccion = "CREATE SEQUENCE secuencia_prestadores START WITH 1 INCREMENT BY 1 NOCACHE NOCYCLE ";
        BD::query.prepare(instruccion);
        ejecutar("Crear Secuencia de Prestadores");
        instruccion = "CREATE OR REPLACE TRIGGER trigger_pk_prestadores BEFORE INSERT ON PRESTADORES FOR EACH ROW "
                        "BEGIN "
                            ":new.idprestador := TO_CHAR(secuencia_prestadores.nextval); "
                        "END; ";
        BD::query.prepare(instruccion);
        ejecutar("Crear Trigger Key de Prestadores");
    }
}

bool BD::agregarPrestador(){
    instruccion="INSERT INTO PRESTADORES (razon_social, cuit, nombre, telefono, direccion, mail)";
    instruccion.append(" VALUES (");
    instruccion.append("  '"+prestador.razon_social+"'");
    instruccion.append(", '"+prestador.cuit+"'");
    instruccion.append(", '"+prestador.nombre+"'");
    instruccion.append(", '"+prestador.telefono+"'");
    instruccion.append(", '"+prestador.direccion+"'");
    instruccion.append(", '"+prestador.mail+"'");
    instruccion.append(") ");
    BD::query.prepare(instruccion);
    bool b=ejecutar("Agregar Prestador");
    ultimoPrestadorAgregado();
    return b;
}

void BD::buscarPrestador(QString busqueda){
    model->clear();
    abrir();
    model->setQuery("SELECT idprestador, nombre, razon_social, telefono, mail, cuit, direccion "
                    " FROM PRESTADORES "+busqueda+" ORDER BY (nombre)", BD::db);
}

void BD::actualizarPrestador(){
    instruccion="UPDATE PRESTADORES SET ";
    instruccion.append("  razon_social='"+prestador.razon_social+"'");
    instruccion.append(", cuit='"+prestador.cuit+"'");
    instruccion.append(", nombre='"+prestador.nombre+"'");
    instruccion.append(", telefono='"+prestador.telefono+"'");
    instruccion.append(", direccion='"+prestador.direccion+"'");
    instruccion.append(", mail='"+prestador.mail+"'");
    instruccion.append(" WHERE idprestador='"+idPrestador+"'");
    BD::query.prepare(instruccion);
    ejecutar("Actualizar Prestador");
}

void BD::eliminarPrestador(){
    BD::query.prepare("DELETE FROM PRESTADORES WHERE idprestador='"+idPrestador+"'");
    ejecutar("Eliminar Prestador");
}

void BD::ultimoPrestadorAgregado(){
    BD::query.prepare("SELECT secuencia_prestadores.NEXTVAL FROM DUAL");
    ejecutar();
    BD::query.prepare("SELECT secuencia_prestadores.CURRVAL FROM DUAL");
    ejecutar();
    BD::query.prepare("ALTER SEQUENCE secuencia_prestadores INCREMENT BY -1");
    ejecutar();
    BD::query.prepare("SELECT secuencia_prestadores.NEXTVAL FROM DUAL");
    ejecutar();
    BD::query.prepare("SELECT secuencia_prestadores.CURRVAL FROM DUAL");
    ejecutar();
    BD::query.next();
    idPrestador=BD::query.value(0).toString();
    BD::query.prepare("ALTER SEQUENCE secuencia_prestadores INCREMENT BY 1");
    ejecutar();
}

bool BD::existeNombrePrestador(QString nombre){
    BD::query.prepare("SELECT COUNT(*) FROM PRESTADORES WHERE nombre='"+nombre+"' AND activado=1");
    ejecutar();
    BD::query.next();
    bool b=0!=BD::query.value(0).toInt();
    return b;
}

void BD::buscarSaldoPrestadores(QString busqueda)
{
    model->clear();
    model->setQuery("SELECT p.idprestador, p.razon_social, (s.nombre || ' ' || s.apellido) AS nombre, c.idcompra, (c.cantcuota - c.cuotaact + 1) AS cuotasadeudadas, c.monto "
                    " FROM prestadores p JOIN compras c ON c.idprestador=p.idprestador JOIN socios s ON c.idsocio=s.idsocio "
                    " WHERE p.idprestador IN (SELECT idprestador FROM prestadores " + busqueda+ ") AND c.terminado=0 ORDER BY (p.razon_social)", BD::db);
}


/*******************************  FIN PRESTADORES  *******************************/



/*******************************  COMPRAS  *******************************/

void BD::crearTablaCompras(){
    instruccion="CREATE TABLE COMPRAS ( "
                      "idcompra          VARCHAR2(10) NOT NULL, "
                      "idsocio           VARCHAR2(10) NOT NULL, "
                      "idprestador       VARCHAR2(10) NOT NULL, "
                      "monto             NUMBER(15,2) NOT NULL, "
                      "cantcuota         NUMBER(7,0) NOT NULL, "
                      "cuotaact          NUMBER(7,0) NOT NULL, "
                      "tipo              VARCHAR2(10) , "
                      "fechamodificacion DATE DEFAULT SYSDATE NOT NULL, "
                      "fechaautorizacion DATE DEFAULT SYSDATE NOT NULL, "
                      "observaciones     VARCHAR2(50) , "
                      "terminado         NUMBER(1,0) NOT NULL, "
                      "activado          NUMBER(1,0) DEFAULT 1 NOT NULL, "
                   "constraint        COMPRAS_PK primary key (idcompra) "
                   ") ";
    BD::query.prepare(instruccion);
    if (ejecutar("Crear Tabla Compras")){
        instruccion = "CREATE SEQUENCE secuencia_compras START WITH 1 INCREMENT BY 1 NOCACHE NOCYCLE ";
        BD::query.prepare(instruccion);
        ejecutar("Crear Secuencia de Compras");
        instruccion = "CREATE OR REPLACE TRIGGER trigger_pk_compras BEFORE INSERT ON COMPRAS FOR EACH ROW "
                        "BEGIN "
                            ":new.idcompra := TO_CHAR(secuencia_compras.nextval); "
                        "END; ";
        BD::query.prepare(instruccion);
        ejecutar("Crear Trigger Key de Compras");
    }
}

bool BD::agregarCompra(){
    instruccion="INSERT INTO COMPRAS (idsocio, idprestador, monto, cantcuota, cuotaact, tipo, observaciones, terminado)";
    instruccion.append(" VALUES (");
    instruccion.append("  '"+idSocio+"'");
    instruccion.append(", '"+idPrestador+"'");
    instruccion.append(",  "+compra.monto);
    instruccion.append(",  "+compra.cantcuotas);
    instruccion.append(",  "+compra.cuotaact);
    instruccion.append(", '"+compra.tipo+"'");
    instruccion.append(", '"+compra.observaciones+"'");
    instruccion.append(",  "+compra.terminado);
    instruccion.append(") ");
    BD::query.prepare(instruccion);
    bool b=ejecutar("Agregar Compra");
    ultimoCompraAgregado();
    return b;
}

void BD::actualizarCompra()
{
    instruccion="UPDATE COMPRAS SET ";
    instruccion.append("  idsocio='"+idSocio+"'");
    instruccion.append(", idprestador='"+idPrestador+"'");
    instruccion.append(", monto='"+compra.monto+"'");
    instruccion.append(", cantcuota="+compra.cantcuotas);
    instruccion.append(", cuotaact="+compra.cuotaact);
    instruccion.append(", tipo='"+compra.tipo+"'");
    instruccion.append(", observaciones='"+compra.observaciones+"'");
    instruccion.append(",  terminado="+compra.terminado);
    instruccion.append(" WHERE idcompra='"+idCompra+"'");
    BD::query.prepare(instruccion);
    ejecutar("Actualizar Prestador");
}

void BD::buscarCompra(QString busqueda){
    qDebug()<<busqueda;
    model->clear();
    abrir();
    model->setQuery("SELECT compras.idcompra, compras.idsocio, (socios.nombre||' '||socios.apellido), compras.idprestador, prestadores.nombre, compras.monto, compras.cantcuota, compras.cuotaact, compras.tipo, compras.observaciones, TO_CHAR(compras.fechaautorizacion, 'dd-MM-yyyy'), TO_CHAR(compras.fechamodificacion, 'dd-MM-yyyy') "
                    " FROM COMPRAS inner join SOCIOS ON compras.idsocio = socios.idsocio inner join PRESTADORES ON compras.idprestador = prestadores.idprestador "+busqueda+" ORDER BY (fechamodificacion)", BD::db);    
}

void BD::eliminarCompra(){
    BD::query.prepare("DELETE FROM COMPRAS WHERE idcompra='"+idCompra+"'");
    ejecutar("Eliminar Compra");
}

void BD::ultimoCompraAgregado(){
    BD::query.prepare("SELECT secuencia_compras.NEXTVAL FROM DUAL");
    ejecutar();
    BD::query.prepare("SELECT secuencia_compras.CURRVAL FROM DUAL");
    ejecutar();
    BD::query.prepare("ALTER SEQUENCE secuencia_compras INCREMENT BY -1");
    ejecutar();
    BD::query.prepare("SELECT secuencia_compras.NEXTVAL FROM DUAL");
    ejecutar();
    BD::query.prepare("SELECT secuencia_compras.CURRVAL FROM DUAL");
    ejecutar();
    BD::query.next();
    idCompra=BD::query.value(0).toString();
    BD::query.prepare("ALTER SEQUENCE secuencia_compras INCREMENT BY 1");
    ejecutar();
}

/******************************* FIN COMPRAS  *******************************/



/*******************************  CIERRES  *******************************/

void BD::crearTablaCierres(){
    instruccion="CREATE TABLE CIERRES ( "
                      "fechainicio       DATE NOT NULL, "
                      "fechafinal        DATE NOT NULL, "
                      "idempresa         VARCHAR2(10) DEFAULT '-1', "
                   "constraint        CIERRES_PK primary key (fechainicio, fechafinal, idempresa) "
                   ") ";
    BD::query.prepare(instruccion);
    ejecutar("Crear Tabla Cierres");
    instruccion="INSERT INTO CIERRES (fechainicio, fechafinal) VALUES ( TO_DATE( '25-02-2015' ,'dd-MM-yyyy'),TO_DATE( '25-02-2015' ,'dd-MM-yyyy') ) ";
    BD::query.prepare(instruccion);
    ejecutar("Agregar Cierre Pibote");
}

void BD::agregarCierre(QString idemp){
    BD::query.prepare("SELECT MAX(fechafinal) FROM CIERRES WHERE idempresa='"+idemp+"' OR idempresa='-1'");
    ejecutar();
    BD::query.next();
    QString fecha_actualizacion = query.value(0).toDate().toString("dd-MM-yyyy");
    QString ultimo_mes_cierre = fecha_actualizacion;
    // En caso de que no haya ninguna fecha anterior:
    if (fecha_actualizacion==NULL) {
        ultimo_mes_cierre = "No se registran cierres anteriores.";
        fecha_actualizacion = QDate::currentDate().toString("dd-MM-yyyy");
    }
    int mes_actualizacion = query.value(0).toDate().month();
    int meshoy = QDate::currentDate().month();
    QString fechahoy = QDate::currentDate().toString("dd-MM-yyyy");
    QMessageBox::StandardButton reply0=QMessageBox::Ok;
    QMessageBox::StandardButton reply1=QMessageBox::No;
    QMessageBox::StandardButton reply2=QMessageBox::No;
    GrupoFlia *gf= new GrupoFlia();
    if (meshoy==mes_actualizacion) {
        if (idemp=="-1") {
            reply0=QMessageBox::critical(gf, "Dos Cierres para el mismo mes!!!"
                                  , "Ya se realizo un cierre para este mes. \n"
                                    "El ultimo cierre mensual fue el: "+fecha_actualizacion+". \n"
                                    "No se puede hacer otro cierre mensual para el corriente mes!!! "
                                  , QMessageBox::Ok);
        } else {
            reply0=QMessageBox::critical(gf, "Dos Cierres para el mismo mes para esta empresa!!!"
                                         , "Ya se realizo un cierre de " + empresa.nombre + "este mes. \n"
                                    "El ultimo cierre mensual fue el: "+fecha_actualizacion+". \n"
                                    "No se puede hacer otro cierre mensual para el corriente mes!!! "
                                  , QMessageBox::Ok);
        }
    } else{
        QString line2 = "Si continua se efectuara el cierre mensual. \n";
        if (idemp!="-1") line2 = "Si continua se efectuara el cierre mensual para " + empresa.nombre +"\n";
        reply1=QMessageBox::information(gf, "Desea Continuar?"
                              , line2 +
                                "El ultimo cierre mensual fue el: "+ultimo_mes_cierre+". \n"
                                "En caso afirmativo se le pedira otra confirmacion."
                              , QMessageBox::Ok|QMessageBox::No);
        if (reply1==QMessageBox::Ok){
            reply2=QMessageBox::information(gf, "Esta Seguro Que Desea Continuar?"
                                     , line2 +
                                       "Todas las cuotas correspondientes se incrementaran en 1 y se imprimiran las planillas de cierre para las empresas. \n"
                                       "Esta accion no se puede deshacer.\n\n Importante: Las empresas que hayan tenido cierres particulares en este mes\n no seran tenidas en cuenta."
                                     , QMessageBox::Ok|QMessageBox::No);
            if (reply2==QMessageBox::Ok){
                if (idemp=="-1") {
                    d_espera = new DialogEspera();
                    d_espera->setModal (true);
                    d_espera->show ();
                    instruccion = "SELECT distinct idempresa FROM EMPRESAS WHERE activado=1 AND idempresa NOT IN (SELECT idempresa FROM CIERRES WHERE idempresa <>'-1' AND (extract(month from sysdate)=extract(month from fechafinal)))";
                    slidsempresa.clear();
                    BD::query.prepare(instruccion);
                    ejecutar();
                    while (BD::query.next()) {
                        slidsempresa.append(BD::query.value(0).toString());
                    }
                    progressIncrement = static_cast<int>(((100/ slidsempresa.size())+0.5f));
                    for (int i=0; i<slidsempresa.size();i++){
                        idEmpresa=slidsempresa.at(i);
                        d_espera->updateValue(progressIncrement);
                        BD::query.prepare("SELECT MAX(fechafinal) FROM CIERRES WHERE idempresa='"+idEmpresa+"'");
                        ejecutar();
                        BD::query.next();
                        mes_actualizacion = query.value(0).toDate().month();
                        if (mes_actualizacion!=meshoy) {
                            instruccion="UPDATE COMPRAS SET ";
                            instruccion.append("  terminado=1");
                            instruccion.append(", fechamodificacion=TO_DATE('"+fechahoy+"','dd-MM-yyyy')");
                            instruccion.append(" WHERE (terminado=0 AND cuotaact=cantcuota) AND idsocio in (SELECT idsocio FROM socios WHERE idempresa='"+idEmpresa+"')");
                            BD::query.prepare(instruccion);
                            ejecutar();
                            instruccion="UPDATE COMPRAS SET ";
                            instruccion.append("  fechamodificacion=TO_DATE('"+fechahoy+"','dd-MM-yyyy')");
                            instruccion.append(", cuotaact = cuotaact+1");
                            instruccion.append(" WHERE terminado=0 AND idsocio in (SELECT idsocio FROM socios WHERE idempresa='"+idEmpresa+"')");
                            BD::query.prepare(instruccion);
                            ejecutar();
                        }
                    }
                    d_espera->close();
                } else {
                    instruccion="UPDATE COMPRAS SET ";
                    instruccion.append("  terminado=1");
                    instruccion.append(", fechamodificacion=TO_DATE('"+fechahoy+"','dd-MM-yyyy')");
                    instruccion.append(" WHERE (terminado=0 AND cuotaact=cantcuota) AND idsocio in (SELECT idsocio FROM socios WHERE idempresa='"+idemp+"')");
                    BD::query.prepare(instruccion);
                    ejecutar();
                    instruccion="UPDATE COMPRAS SET ";
                    instruccion.append("  fechamodificacion=TO_DATE('"+fechahoy+"','dd-MM-yyyy')");
                    instruccion.append(", cuotaact = cuotaact+1");
                    instruccion.append(" WHERE terminado=0 AND idsocio in (SELECT idsocio FROM socios WHERE idempresa='"+idemp+"')");
                    BD::query.prepare(instruccion);
                    ejecutar();
                }
                instruccion="INSERT INTO CIERRES (fechainicio, fechafinal, idempresa) VALUES (TO_DATE('"+fecha_actualizacion+"','dd-MM-yyyy'), TO_DATE('"+fechahoy+"','dd-MM-yyyy'),'"+idemp+"') ";
                BD::query.prepare(instruccion);
                ejecutar("Cierre Mensual");
                printCierreMensual(idemp);
            }
        }
    }
}

void BD::printCierreMensual(QString idemp){
    BD::query.prepare("SELECT MAX(fechafinal) FROM CIERRES WHERE idempresa='"+idemp+"' OR idempresa='-1'");
    ejecutar();
    BD::query.next();
    GrupoFlia *gf= new GrupoFlia();
    QString fecha_actualizacion = query.value(0).toDate().toString("dd-MM-yyyy");
    QMessageBox::information(gf, "Generacion de Informes"
                                  , "Se generan los informes para las empresas respectivos al ultimo cierre mensual el cual fue: "+fecha_actualizacion+". \n"
                                    "Por favor sea PACIENTE y no haga nada hasta que los informes sean generados. \n"
                                  , QMessageBox::Ok);

    QString path = QFileDialog::getExistingDirectory(0, tr("Seleccionar Carpeta"));
    if (path!=""){
        d_espera = new DialogEspera();
        d_espera->setModal (true);
        d_espera->show ();
        QStringList id;
        QStringList apellido;
        QStringList nombre;
        QStringList dni;
        QStringList cuotasocio;
        QStringList grupofamiliar;
        QStringList cuotaclub;
        QStringList compras;
        QStringList prestamos;
        QStringList totales;
        instruccion="SELECT valor FROM MONTOS WHERE nombre='"+numCuota+"'";
        BD::query.prepare(instruccion);
        ejecutar();
        BD::query.next();
        QString cuota = QStringMoney::number(BD::query.value(0).toDouble());
        instruccion="SELECT valor FROM MONTOS WHERE nombre='"+numFlia+"'";
        BD::query.prepare(instruccion);
        ejecutar();
        BD::query.next();
        QString flia = QStringMoney::number(BD::query.value(0).toDouble());
        instruccion="SELECT valor FROM MONTOS WHERE nombre='"+numPorve+"'";
        BD::query.prepare(instruccion);
        ejecutar();
        BD::query.next();
        QString porve = QStringMoney::number(BD::query.value(0).toDouble());

        if (idemp!="-1") {
            slidsempresa.append(idemp);
        }
        QTime *timer=new QTime();
        timer->start();
        for (int i=0; i<slidsempresa.size();i++){
            idEmpresa=slidsempresa.at(i);
            d_espera->updateValue(progressIncrement);
            cargarEmpresaPorId();
            instruccion = "SELECT distinct socios.idsocio, socios.apellido, socios.nombre, socios.dni, socios.grupofamiliar, socios.clubporve "
                    ", (SELECT SUM(compras.monto) FROM COMPRAS WHERE (socios.idsocio = compras.idsocio AND compras.tipo = 'COMPRA' AND (compras.fechamodificacion=TO_DATE('"+fecha_actualizacion+"','dd-MM-yyyy')) AND compras.activado=1))"
                    ", (SELECT SUM(compras.monto) FROM COMPRAS WHERE (socios.idsocio = compras.idsocio AND compras.tipo = 'PRESTAMO' AND (compras.fechamodificacion=TO_DATE('"+fecha_actualizacion+"','dd-MM-yyyy')) AND compras.activado=1))"
                    "FROM SOCIOS inner join EMPRESAS ON socios.idempresa = empresas.idempresa "
                    "left join COMPRAS ON socios.idsocio = compras.idsocio "
                    "WHERE (socios.idempresa='"+idEmpresa+"' AND socios.activado=1) ORDER BY (socios.apellido)";

            QDir dir(path+"/CIERRES/"+empresa.nombre);
            if (!dir.exists())
                dir.mkpath(".");
            QString py=path+"/CIERRES/"+empresa.nombre+"/"+fecha_actualizacion;

            query.prepare(instruccion);
            id.clear();
            apellido.clear();
            nombre.clear();
            dni.clear();
            cuotasocio.clear();
            grupofamiliar.clear();
            cuotaclub.clear();
            compras.clear();
            prestamos.clear();
            totales.clear();
            ejecutar();
            double t=0;
            while (BD::query.next()){
                id.append(BD::query.value(0).toString());
                apellido.append(BD::query.value(1).toString());
                nombre.append(BD::query.value(2).toString());
                dni.append(BD::query.value(3).toString());
                cuotasocio.append(cuota);
                if (BD::query.value(4).toString()!=SI)
                    grupofamiliar.append(QStringMoney::number(0));
                else
                    grupofamiliar.append(flia);
                if (BD::query.value(5).toString()!=SI)
                    cuotaclub.append(QStringMoney::number(0));
                else
                    cuotaclub.append(porve);
                if (BD::query.value(6).isNull())
                    compras.append(QStringMoney::number(0));
                else
                    compras.append(QStringMoney::number(BD::query.value(6).toDouble()));
                if (BD::query.value(7).isNull())
                    prestamos.append(QStringMoney::number(0));
                else
                    prestamos.append(QStringMoney::number(BD::query.value(7).toDouble()));
                double d=cuotasocio.last().toDouble()
                        +grupofamiliar.last().toDouble()
                        +cuotaclub.last().toDouble()
                        +compras.last().toDouble()
                        +prestamos.last().toDouble();
                totales.append(QStringMoney::number(d));
                t = t + d;
            }
            PrintCierre::PrintCierre(id,apellido,nombre,dni,cuotasocio,grupofamiliar,cuotaclub,compras,prestamos,totales,py,t);
            while(timer->elapsed()<700) QApplication::processEvents();
            timer->restart();
        }
        if (idemp!="-1") {
            slidsempresa.clear();
        }
        d_espera->close();
        delete timer;
        QMessageBox::information(gf,"GENERAR INFORMES",QString("Operación realizada con éxito!."));
    }
}

bool BD::hoySeHizoCierre(){
    BD::query.prepare("SELECT MAX(fechafinal) FROM CIERRES WHERE idempresa=-1");
    ejecutar();
    BD::query.next();
    QString fecha_actualizacion = query.value(0).toDate().toString("dd-MM-yyyy");
    QString fechahoy = QDate::currentDate().toString("dd-MM-yyyy");
    return fecha_actualizacion==fechahoy;
}

/*******************************  CIERRES  *******************************/



/*******************************  MONTOS  *******************************/

void BD::crearTablaMontos(){
    instruccion="CREATE TABLE MONTOS ( "
            "nombre   VARCHAR2(30) NOT NULL, "
            "valor    NUMBER(7,2) NOT NULL, "
            "constraint  MONTOS_PK primary key (nombre) "
                   ") ";
    BD::query.prepare(instruccion);
    ejecutar("Crear Tabla Montos");
    instruccion="INSERT INTO MONTOS (nombre,valor) VALUES ('"+numCuota+"', 100.89) ";
    BD::query.prepare(instruccion);
    ejecutar("Agregar "+numCuota);
    instruccion="INSERT INTO MONTOS (nombre,valor) VALUES ('"+numFlia+"', 50.61) ";
    BD::query.prepare(instruccion);
    ejecutar("Agregar "+numFlia);
    instruccion="INSERT INTO MONTOS (nombre,valor) VALUES ('"+numPorve+"', 50) ";
    BD::query.prepare(instruccion);
    ejecutar("Agregar "+numPorve);
}

void BD::actualizarMonto(QString nombre, QString valor){
    instruccion="UPDATE MONTOS SET valor="+valor+" WHERE nombre='"+nombre+"'";
    BD::query.prepare(instruccion);
    ejecutar("Actualizar "+nombre);
}

double BD::obtenerMonto(QString nombre){
    instruccion="SELECT valor FROM MONTOS WHERE nombre='"+nombre+"'";
    BD::query.prepare(instruccion);
    ejecutar();
    BD::query.next();
    return BD::query.value(0).toDouble();
}

/******************************* FIN MONTOS  *******************************/
