#include "pig.h"
#include<QDebug>

/*pig::pig(QObject *parent) : QObject(parent)
{

}*/
pig::pig(){

}
pig::pig(double init_weight,int init_kind,int init_price,int init_pighouse){
    this->weight=init_weight;
    this->kind=init_kind;
    this->price=init_price;
    this->num=-1;  //设为-1
    this->pighouse=init_pighouse;
    this->existTime=0;
    this->isill=0;
}
void pig::setisill(bool x){
    this->isill=x;
}
void pig::setkind(int x){
    this->kind=x;
}
void pig::setprice(int x){
    this->price=x;
}
void pig::setweight(double x){
    this->weight=x;
}
void pig::setnum(int x){
    this->num=x;
}
void pig::setpighouse(int x){
    this->pighouse=x;
}
int pig::getkind(){
   /* if(kind==1)
        qDebug()<<"黑猪";
        if(kind==2)
        qDebug()<<"小花猪";
        if(kind==3)
        qDebug()<<"大白花猪";*/
    return kind;
}
double pig::getweight(){
    return weight;
}
int pig::getprice(){
        return price;
}
int pig::getexistTime(){
    return existTime;
}
int pig::getnum(){
    return num;
}
int pig::getpighouse(){
        return pighouse;
}
bool pig::getisill(){
    return isill;
}
void pig::show(){
    qDebug()<<kind<<"       "<<weight<<"       "<<price <<"       "
            <<pighouse;
}
void pig::weightgrow(){
    this->weight+=(rand()%12)/10.0;//一天增重0.0~1.2kg
    this->existTime+=1;  //养育时间增加
}
