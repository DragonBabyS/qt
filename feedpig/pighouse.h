#ifndef PIGHOUSE_H
#define PIGHOUSE_H

#include <QObject>
#include<QList>
#include<pig.h>

class Pighouse : public QObject
{
    Q_OBJECT
    int num;
    int size;
    int black_num;
    int xiaohua_num;
    int dahua_num;
public:
    explicit Pighouse(QObject *parent = nullptr);
    QList<pig*>pg;
    int pig_out();
    void pig_in(pig*pg);

    void setnum(int x);
    void setsize(int x);
    void setblack_num(int x);
    void setxiaohua_num(int x);
    void setdahua_num(int x);
    int getnum();
    int getsize();
    int getblack_num();
    int getxiaohua_num();
    int getdahua_num();
signals:

public slots:
};

#endif // PIGHOUSE_H
