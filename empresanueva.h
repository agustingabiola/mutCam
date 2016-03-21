#ifndef EMPRESANUEVA_H
#define EMPRESANUEVA_H

#include <QDialog>
#include <QStandardItemModel>
#include "bd.h"

namespace Ui {class EmpresaNueva;}

class EmpresaNueva : public QDialog{
    Q_OBJECT
    
public:
    explicit EmpresaNueva(QWidget *parent = 0);
    ~EmpresaNueva();
    
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
    Ui::EmpresaNueva *ui;

    void conectarCheckBoxes();
    void setLineEditCuit();

    void cargarAttributosEmpresa();
    void exit();

signals:
    void empresaNuevaTerminado();
};

#endif // EMPRESANUEVA_H
