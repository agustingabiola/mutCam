#ifndef PRINTSOCIOSBUSQUEDA_H
#define PRINTSOCIOSBUSQUEDA_H

#include <QWidget>
#include <QStandardItemModel>
#include <QPrinter>
#include <QPainter>
#include <QDate>
#include <QSqlRecord>
#include "global.h"
#include "dialogespera.h"
#include <QFileDialog>

namespace Ui {
class PrintSociosBusqueda;
}

class PrintSociosBusqueda : public QWidget
{
    Q_OBJECT
    
public:
    explicit PrintSociosBusqueda(QWidget *parent = 0);
    ~PrintSociosBusqueda();
    
private:
    Ui::PrintSociosBusqueda *ui;
    QPrinter printer;

    QString hojamax;
    int hoja;
    static DialogEspera *d_espera;
    int progressIncrement;
};

#endif // PRINTSOCIOSBUSQUEDA_H
