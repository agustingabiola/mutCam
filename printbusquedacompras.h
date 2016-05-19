#ifndef PRINTBUSQUEDACOMPRAS_H
#define PRINTBUSQUEDACOMPRAS_H

#include <QWidget>
#include <QStandardItemModel>
#include <QPrinter>
#include <QPainter>
#include <QDate>
#include <QSqlRecord>
#include "global.h"
#include <QFileDialog>

namespace Ui {
class PrintBusquedaCompras;
}

class PrintBusquedaCompras : public QWidget
{
    Q_OBJECT
    
public:
    explicit PrintBusquedaCompras(QWidget *parent = 0, QString nota = "");
    ~PrintBusquedaCompras();
private:
    Ui::PrintBusquedaCompras *ui;
    QPrinter printer;

    QString hojamax;
    int hoja;
};

#endif // PRINTBUSQUEDACOMPRAS_H
