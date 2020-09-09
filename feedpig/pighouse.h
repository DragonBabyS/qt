#ifndef PIGHOUSE_H
#define PIGHOUSE_H

#include <QObject>
#include<QList>
#include<pig.h>
#include<QFile>

class Pighouse : public QObject
{
    Q_OBJECT
    int num;
    int size;
    int black_num;
    int xiaohua_num;
    int dahua_num;
    int virus;
public:
    explicit Pighouse(QObject *parent = nullptr);
    QList<pig*>pg;
    int pig_out();
    //对猪做出圈处理，如果有猪出卷则添加一批猪，返回猪的出圈售价
    double pigchange(QFile*salelog,int time,int num);//三个参数分别为
    //存储销售记录的文件指针，全局时间，以及当前调用的猪圈编号
    void setvirus(int x);
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
    int getvirus();
signals:

public slots:
};

#endif // PIGHOUSE_H
