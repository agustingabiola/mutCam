#ifndef PRINTPRESTADORBUSQUEDA_H
#define PRINTPRESTADORBUSQUEDA_H

#include <QWidget>
#include <QStandardItemModel>
#include <QPrinter>
#include <QPainter>
#include <QDate>
#include <QSqlRecord>
#include "global.h"
#include <QFileDialog>

namespace Ui {
class PrintPrestadorBusqueda;
}

class PrintPrestadorBusqueda : public QWidget
{
    Q_OBJECT
    
public:
    explicit PrintPrestadorBusqueda(QWidget *parent = 0);
    ~PrintPrestadorBusqueda();
    
private:
    Ui::PrintPrestadorBusqueda *ui;
    QPrinter printer;

    QString hojamax;
    int hoja;
};

#endif // PRINTPRESTADORBUSQUEDA_H
