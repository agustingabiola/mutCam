#ifndef PRINTSALDOPRESTADORES_H
#define PRINTSALDOPRESTADORES_H

#include <QWidget>
#include <QStandardItemModel>
#include <QPrinter>
#include <QPainter>
#include <QDate>
#include <QSqlRecord>
#include "global.h"

namespace Ui {
class PrintSaldoPrestadores;
}

class PrintSaldoPrestadores : public QWidget
{
    Q_OBJECT
    
public:
    explicit PrintSaldoPrestadores(QWidget *parent = 0);
    ~PrintSaldoPrestadores();
    
private:
    Ui::PrintSaldoPrestadores *ui;
    QPrinter printer;

    QString hojamax;
    int hoja;
};

#endif // PRINTSALDOPRESTADORES_H
