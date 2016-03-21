#ifndef EMPRESAEDITAR_H
#define EMPRESAEDITAR_H

#include <QDialog>
#include <QStandardItemModel>
#include "bd.h"

namespace Ui {class EmpresaEditar;}

class EmpresaEditar : public QDialog{
    Q_OBJECT
    
public:
    explicit EmpresaEditar(QWidget *parent = 0);
    ~EmpresaEditar();
    
private slots:
    void todosChequeados();

    void on_lineEditRazonSocial_textEdited(const QString &arg1);
    void on_lineEditCuit_textEdited(const QString &arg1);
    void on_lineEditDireccion_textEdited(const QString &arg1);
    void on_lineEditNombre_textEdited(const QString &arg1);
    void on_lineEditEmail_textEdited(const QString &arg1);
    void on_lineEditTel_textEdited(const QString &arg1);

    void on_pushButtonActualizar_clicked();
    void on_pushButtonEliminar_clicked();
    void on_pushButtonCancelar_clicked();
    void on_pushButtonDeshacer_clicked();

private:
    Ui::EmpresaEditar *ui;
    bool editado;

    void load();
    void conectarCheckBoxes();
    void setLineEditCuit();

    void cargarAttributosEmpresa();
    void exit();

signals:
    void empresaEditarTerminado();
};

#endif // EMPRESAEDITAR_H
