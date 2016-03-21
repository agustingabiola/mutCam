#ifndef SOCIONUEVO_H
#define SOCIONUEVO_H

#include <QDialog>
#include <QStandardItemModel>
#include "bd.h"
#include "grupoflia.h"

namespace Ui {class SocioNuevo;}

class SocioNuevo : public QDialog{
    Q_OBJECT
    
public:
    explicit SocioNuevo(QWidget *parent = 0);
    ~SocioNuevo();
    
private slots:
    void todosChequeados();
    void slotBoton();

    void on_lineEditNombre_textEdited(const QString &arg1);
    void on_lineEditDni_textEdited(const QString &arg1);
    void on_lineEditDireccion_textEdited(const QString &arg1);
    void on_lineEditApellido_textEdited(const QString &arg1);
    void on_lineEditEmail_textEdited(const QString &arg1);
    void on_lineEditTel_textEdited(const QString &arg1);
    void on_lineEditNumSocio_textEdited(const QString &arg1);

    void on_pushButtonAgregar_clicked();
    void on_pushButtonCancelar_clicked();
    void on_pushButtonFlia_clicked();

private:
    Ui::SocioNuevo *ui;
    GrupoFlia *gl;

    void conectarCheckBoxes();
    void setLineEditNums();

    void cargarAttributosSocio();
    void exit();

signals:
    void socioNuevoTerminado();
};

#endif // SOCIONUEVO_H
