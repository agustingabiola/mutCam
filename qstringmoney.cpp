#include "qstringmoney.h"

QStringMoney::QStringMoney()
{
}

QString QStringMoney::number(double d, int p){
    QString s;
    /*/
    s=QString::number(d);
    QString f="%."+QString::number(p)+"f";
    /*/
    s.sprintf("%.2f", d);
    return s;
}
