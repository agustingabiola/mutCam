#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    if (QDateTime::currentDateTime().date().year() >= 2017) {
        QMessageBox::information(0, "Contactarse con el programador!"
                             , "La version de prueba ha expirado!! \n"
                             , QMessageBox::Ok);
        return 0;
    }

    MainWindow w;
    w.show ();
    return a.exec ();
}
