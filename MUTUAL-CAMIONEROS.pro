    #-------------------------------------------------
#
# Project created by QtCreator 2015-01-18T00:42:43
#
#-------------------------------------------------

QT       += core gui sql

TARGET = MUTUAL-CAMIONEROS
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    global.cpp \
    bd.cpp \
    socionuevo.cpp \
    empresanueva.cpp \
    prestadornuevo.cpp \
    empresabuscar.cpp \
    prestadorbuscar.cpp \
    empresaeditar.cpp \
    prestadoreditar.cpp \
    compranuevo.cpp \
    sociobuscar.cpp \
    socioeditar.cpp \
    comprabuscar.cpp \
    grupoflia.cpp \
    printcierre.cpp \
    qstringmoney.cpp \
    dialogespera.cpp \
    printbusquedacompras.cpp \
    compraeditar.cpp \
    prestadoressaldos.cpp \
    printsaldoprestadores.cpp \
    printempresabusqueda.cpp \
    printprestadorbusqueda.cpp

HEADERS  += mainwindow.h \
    global.h \
    bd.h \
    socionuevo.h \
    empresanueva.h \
    prestadornuevo.h \
    empresabuscar.h \
    prestadorbuscar.h \
    empresaeditar.h \
    prestadoreditar.h \
    compranuevo.h \
    sociobuscar.h \
    socioeditar.h \
    comprabuscar.h \
    grupoflia.h \
    printcierre.h \
    qstringmoney.h \
    dialogespera.h \
    printbusquedacompras.h \
    compraeditar.h \
    prestadoressaldos.h \
    printsaldoprestadores.h \
    printempresabusqueda.h \
    printprestadorbusqueda.h

FORMS    += mainwindow.ui \
    socionuevo.ui \
    empresanueva.ui \
    prestadornuevo.ui \
    empresabuscar.ui \
    prestadorbuscar.ui \
    empresaeditar.ui \
    prestadoreditar.ui \
    compranuevo.ui \
    sociobuscar.ui \
    socioeditar.ui \
    comprabuscar.ui \
    grupoflia.ui \
    printcierre.ui \
    dialogespera.ui \
    printbusquedacompras.ui \
    compraeditar.ui \
    prestadoressaldos.ui \
    printsaldoprestadores.ui \
    printempresabusqueda.ui \
    printprestadorbusqueda.ui

RESOURCES += \
    Icons.qrc

win32: RC_FILE += prueba.rc
