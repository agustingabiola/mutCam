#ifndef SOCIOEDITAR_H
#define SOCIOEDITAR_H

#include <QDialog>
#include <QStandardItemModel>
#include "bd.h"
#include "grupoflia.h"

namespace Ui {class SocioEditar;}

class SocioEditar : public QDialog{
    Q_OBJECT
    
public:
    explicit SocioEditar(QWidget *parent = 0);
    ~SocioEditar();
    
private slots:
    void slotEditado();
    void todosChequeados();

    void on_lineEditNombre_textEdited(const QString &arg1);
    void on_lineEditDni_textEdited(const QString &arg1);
    void on_lineEditDireccion_textEdited(const QString &arg1);
    void on_lineEditApellido_textEdited(const QString &arg1);
    void on_lineEditEmail_textEdited(const QString &arg1);
    void on_lineEditTel_textEdited(const QString &arg1);
    void on_lineEditNumSocio_textEdited(const QString &arg1);

    void on_pushButtonActualizar_clicked();
    void on_pushButtonEliminar_clicked();
    void on_pushButtonCancelar_clicked();
    void on_pushButtonDeshacer_clicked();
    void on_pushButtonFlia_clicked();

private:
    Ui::SocioEditar *ui;
    GrupoFlia *gl;
    bool editado;

    void load();
    void conectarCheckBoxes();
    void setLineEditNums();

    void cargarAttributosSocio();
    void exit();

signals:
    void socioEditarTerminado();
};

#endif // SOCIOEDITAR_H
