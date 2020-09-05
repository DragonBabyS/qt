#include "pighouse.h"

Pighouse::Pighouse(QObject *parent) : QObject(parent)
{
  this->num=0;
    this->size=0;
    this->black_num=0;
    this->xiaohua_num=0;
    this->dahua_num=0;
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
