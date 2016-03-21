#ifndef PRESTADORNUEVO_H
#define PRESTADORNUEVO_H

#include <QDialog>
#include <QStandardItemModel>
#include "bd.h"

namespace Ui {class PrestadorNuevo;}

class PrestadorNuevo : public QDialog{
    Q_OBJECT
    
public:
    explicit PrestadorNuevo(QWidget *parent = 0);
    ~PrestadorNuevo();
    
private slots:
    void todosChequeados();

    void on_lineEditRazonSocial_textEdited(const QString &arg1);
    void on_lineEditCuit_textEdited(const QString &arg1);
    void on_lineEditDireccion_textEdited(const QString &arg1);
    void on_lineEditNombre_textEdited(const QString &arg1);
    void on_lineEditEmail_textEdited(const QString &arg1);
    void on_lineEditTel_textEdited(const QString &arg1);

    void on_pushButtonAgregar_clicked();
    void on_pushButtonCancelar_clicked();

private:
    Ui::PrestadorNuevo *ui;

    void conectarCheckBoxes();
    void setLineEditCuit();

    void cargarAttributosPrestador();
    void exit();

signals:
    void prestadorNuevoTerminado();
};

#endif // PRESTADORNUEVO_H
