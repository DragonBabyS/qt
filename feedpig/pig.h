#ifndef PIG_H
#define PIG_H

#include <QObject>

class pig : public QObject
{
    Q_OBJECT
    int kind;//1 for black,2 for xiaohua,3 for dahua
    double weight;
    int price;
    int existTime;
    int num;//猪在猪圈里的编号
    int pighouse;
    bool isill;//记录是否感染猪瘟
public:
    explicit pig(QObject *parent = nullptr);
    pig();
    pig(double init_weight,int init_kind,int init_price,int init_pighouse);//构造函数
    void setisill(bool x);
    void weightgrow();
    void  setkind(int x);
    void setweight(double x);
    void setprice(int x);
    void setnum(int x);
    void setpighouse(int x);
    int getkind();
    double getweight();
    int getprice();
    int getexistTime();
    int getnum();
    int getpighouse();
    bool getisill();
    void show();
signals:

public slots:
};

#endif // PIG_H
