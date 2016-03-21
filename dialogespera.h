#ifndef DIALOGESPERA_H
#define DIALOGESPERA_H

#include <QTimer>
#include <QDialog>

namespace Ui {
    class DialogEspera;
}

class DialogEspera : public QDialog{
    Q_OBJECT

public:
    explicit DialogEspera(QWidget *parent = 0);
    ~DialogEspera();
    void setAceptar (bool visible);
    void setProgressBar (bool value);
    void setInsideText (QString text);
    void updateValue (int value);

private:
    Ui::DialogEspera *ui;

private slots:
    void on_progressBar_valueChanged(int value);
    void on_aceptar_clicked();
signals:
    void dialog_termino (QString );
};

#endif // DIALOGESPERA_H
