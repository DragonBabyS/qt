#include "pighouse.h"
#include<QDebug>
#include"mainwindow.h"
#include<QFile>
#include<QIODevice>
#include<QTextStream>

Pighouse::Pighouse(QObject *parent) : QObject(parent)
{
  this->num=0;
    this->size=0;
    this->black_num=0;
    this->xiaohua_num=0;
    this->dahua_num=0;
    this->virus=0;
}
void Pighouse::setvirus(int x){
    this->virus=x;
}
void Pighouse::setnum(int x){
    this->num=x;
}
void Pighouse::setsize(int x){
    this->size=x;
}
void Pighouse::setblack_num(int x){
    this->black_num=x;
}
void Pighouse::setxiaohua_num(int x){
    this->xiaohua_num=x;
}
void Pighouse::setdahua_num(int x){
    this->dahua_num=x;
}
int Pighouse::getnum(){
    return num;
}
int Pighouse::getsize(){
    return size;
}
int Pighouse::getblack_num(){
    return black_num;
}
int Pighouse::getxiaohua_num(){
    return xiaohua_num;
}
int Pighouse::getdahua_num(){
    return dahua_num;
}
int Pighouse::getvirus(){
    return virus;
}
double Pighouse::pigchange(QFile*salelog,int time,int num){
    double saleprice=0;//出圈售价
    int presize=size;//移除之前的猪圈猪总数
    int outnumber=0;//本次移除猪的数量
    for(int i=0;i<size;i++){
        if(pg[i]->getweight()>=150||pg[i]->getexistTime()>365){
            if(pg[i]->getkind()==1){
                black_num--;
                saleprice+=15*pg[i]->getweight();
            }
            if(pg[i]->getkind()==2){
               xiaohua_num--;
                saleprice+=7*pg[i]->getweight();
            }
            if(pg[i]->getkind()==3){
                dahua_num--;
                saleprice+=6*pg[i]->getweight();
            }
            size--;
            outnumber++;
            pg.removeAt(i);//将猪移除猪圈
        }
    }
    //存入销售记录
    if(outnumber!=0){
        salelog->open(QIODevice::ReadWrite|QIODevice::Append);
                QTextStream out(salelog);
              int month=time/30;
               out <<QString("第")<<month<<QString("个月          ") <<num<<"               "<<
                outnumber<<"              "<<
                saleprice<<"\n";
               salelog->close() ;
    }

    //重新设置编号
    int cursize=presize-outnumber;//剩余猪的数量
    for(int i=0;i<cursize;i++)
        pg[i]->setnum(i);
      return saleprice;
    }



