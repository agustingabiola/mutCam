#ifndef PRINTCIERRE_H
#define PRINTCIERRE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QDate>
#include <QPrinter>
#include <QPainter>
#include "global.h"

namespace Ui {class PrintCierre;}

class PrintCierre : public QWidget{
    Q_OBJECT
    
public:
    explicit PrintCierre(QStringList id,
                         QStringList apellido,
                         QStringList nombre,
                         QStringList dni,
                         QStringList cuotasocio,
                         QStringList grupofamiliar,
                         QStringList cuotaclub,
                         QStringList compras,
                         QStringList cheques,
                         QStringList totales,                        
                         QString pathy,
                         double d,
                          QWidget *parent = 0);
    ~PrintCierre();
    
private:
    Ui::PrintCierre *ui;
    QStandardItemModel *model;
    QPrinter printer;

    QString hojamax;
    int hoja;

    void  printAux(QString pathy);
    QString getTotal(QStringList totals);
};

#endif // PRINTCIERRE_H

