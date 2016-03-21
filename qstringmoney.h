#ifndef QSTRINGMONEY_H
#define QSTRINGMONEY_H

#include<QString>

class QStringMoney
{
public:
    QStringMoney();

     static QString number(double d, int p=2);
};

#endif // QSTRINGMONEY_H
