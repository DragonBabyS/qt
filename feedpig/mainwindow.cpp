#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include"pig.h"
#include<QPainter>
#include<QPixmap>
#include<QDebug>
#include<QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setMaximum(1000);//调整滑条的最大值
    //初始化猪圈编号0-99
    for(int i=0;i<100;i++){
        ph[i].setnum(i);
    }

    //添加猪
    srand((unsigned)time(NULL));
    connect(ui->pushButton,&QPushButton::clicked,
            [=]{
        int add_num=ui->spinBox->value();
        qDebug()<<"猪的品种  "<<"猪的体重  "<<
                  "猪的价格   "<<"猪所在圈数";
        for(int i=0;i<add_num;i++){
            double a_weight=(200+rand()%300)/10.0;

               int a_pighouse=rand()%100;
              int a_kind=1+rand()%3;

              int a_price;
                if(a_kind==1)
                a_price=15;
                else if(a_kind==2)
                a_price=7;
                else if(a_kind==3)
                 a_price=6;
                pig*pigs=new pig(a_weight,a_kind,a_price,a_pighouse);
                bool flag=1;//flag用于记录是否构造成功
                if(a_kind==1){  /*若为黑猪，则当前猪圈里不能有小花猪，大花猪，且不能超过一个猪圈
                   的最大容量--10只 */
                    if(ph[a_pighouse].getxiaohua_num()==0&&ph[a_pighouse].getdahua_num()==0
                            &&ph[a_pighouse].getsize()<10){
                         ph[a_pighouse].pg.push_back(pigs);//猪进圈
                          int a_num=ph[a_pighouse].getsize(); //设置编号
                          pigs->setnum(a_num);
                    }

                    else{
                        i--;
                        flag=0;
                        delete pigs;

                    }
                }
               else{   //若不为黑猪，则当前猪圈里不能有黑猪，且不能超出容量
                    if(ph[a_pighouse].getblack_num()==0&&ph[a_pighouse].getsize()<10){
                         ph[a_pighouse].pg.push_back(pigs);
                         int a_num=ph[a_pighouse].getsize();    //设置编号
                         pigs->setnum(a_num);
                       }
                    else{
                        i--;
                        flag=0;
                        delete pigs;
                    }
                }
                if(flag){
                    pigs->show();//显示成功的构造信息
                    if(a_kind==1)ph[a_pighouse].setblack_num(ph[a_pighouse].getblack_num()+1);
                    if(a_kind==2)ph[a_pighouse].setxiaohua_num(ph[a_pighouse].getxiaohua_num()+1);
                    if(a_kind==3)ph[a_pighouse].setdahua_num(ph[a_pighouse].getdahua_num()+1);
                    ph[a_pighouse].setsize(ph[a_pighouse].getsize()+1);
              }

        }
        qDebug()<<"添加成功";
        });

    //查询猪圈
    connect(ui->pushButton_2,&QPushButton::clicked,
            [=]{
        searchpighouse();
    }
            );

    //查询单只猪
    connect(ui->pushButton_7,&QPushButton::clicked,
            [=]{
        searchonepig();
    }
            );

    //统计整个猪场每个品种猪的数量和体重、饲养时间分布情况
    connect(ui->pushButton_16,&QPushButton::pressed,
            [=]{
        sum();
    }
            );
    }

//查询猪圈信息函数
void MainWindow::searchpighouse(){
    int ans=ui->spinBox_2->value();
    qDebug()<<"查询的是猪圈"<<ans;
    int black=ph[ans].getblack_num();
    int xiaohua=ph[ans].getxiaohua_num();
    int dahua=ph[ans].getdahua_num();
    int sum=ph[ans].getsize();
    ui->lineEdit->setText(QString::number(sum));
    ui->lineEdit_2->setText(QString::number(black));
    ui->lineEdit_3->setText(QString::number(xiaohua));
    ui->lineEdit_4->setText(QString::number(dahua));
}

//查询单只猪信息函数
void MainWindow::searchonepig(){
    int ans=ui->spinBox_3->value();//猪圈号
    int ans2=ui->spinBox_4->value();//猪编号
    if(ans2>=ph[ans].getsize()){
        ui->lineEdit_5->clear();//若此猪不存在，则清空行文本编辑器里的内容
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();
        qDebug()<<"当前猪圈里没有此编号的猪";
        return;
    }
qDebug()<<"查询的是猪圈"<<ans<<"里编号为"<<ans2<<"的猪";
double weight=ph[ans].pg[ans2]->getweight();
int kind=ph[ans].pg[ans2]->getkind();
int price=ph[ans].pg[ans2]->getprice();
int existtime=ph[ans].pg[ans2]->getexistTime();
switch(kind){
case 1:ui->lineEdit_5->setText("黑猪");
    break;
case 2:ui->lineEdit_5->setText("小花猪");
    break;
case 3:ui->lineEdit_5->setText("大花白猪");
    break;
default:break;
}
ui->lineEdit_6->setText(QString::number(weight));
ui->lineEdit_7->setText(QString::number(price));
ui->lineEdit_8->setText(QString::number(existtime));

}


//统计整个猪场每个品种猪的数量和体重、饲养时间分布情况函数
void MainWindow::sum(){
    int s_black=0,s_xiaohua=0,s_dahua=0;
    double w1=0,w2=0,w3=0;
    for(int i=0;i<100;i++){
        s_black+=ph[i].getblack_num();
        s_xiaohua+=ph[i].getxiaohua_num();
        s_dahua+=ph[i].getdahua_num();
        for(int j=0;j<ph[i].getsize();j++){
           if(ph[i].pg[j]->getkind()==1)
               w1+=ph[i].pg[j]->getweight();
           if(ph[i].pg[j]->getkind()==2)
               w2+=ph[i].pg[j]->getweight();
           if(ph[i].pg[j]->getkind()==3)
               w3+=ph[i].pg[j]->getweight();
        }
    }
    ui->lineEdit_9->setText(QString::number(s_black));
    ui->lineEdit_10->setText(QString::number(w1)+" kg");
    ui->lineEdit_11->setText(QString::number(s_xiaohua));
    ui->lineEdit_12->setText(QString::number(w2)+" kg");
    ui->lineEdit_13->setText(QString::number(s_dahua));
    ui->lineEdit_14->setText(QString::number(w3)+" kg");
}


//传背景图
void MainWindow::paintEvent(QPaintEvent *e){
    QPainter p(this);
   p.drawPixmap(0,0,width(),height(),QPixmap("://bf3098fed05e43659944683979ed374f.jpeg"));

}


MainWindow::~MainWindow()
{
    delete ui;
}
