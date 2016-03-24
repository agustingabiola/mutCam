#ifndef PRINTEMPRESABUSQUEDA_H
#define PRINTEMPRESABUSQUEDA_H

#include <QWidget>
#include <QStandardItemModel>
#include <QPrinter>
#include <QPainter>
#include <QDate>
#include <QSqlRecord>
#include "global.h"

namespace Ui {
class PrintEmpresaBusqueda;
}

class PrintEmpresaBusqueda : public QWidget
{
    Q_OBJECT
    
public:
    explicit PrintEmpresaBusqueda(QWidget *parent = 0);
    ~PrintEmpresaBusqueda();
    
private:
    Ui::PrintEmpresaBusqueda *ui;
    QPrinter printer;

    QString hojamax;
    int hoja;
};

#endif // PRINTEMPRESABUSQUEDA_H
