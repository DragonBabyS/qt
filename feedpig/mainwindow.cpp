#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QApplication>
#include<QPushButton>
#include"pig.h"
#include<QPainter>
#include<QPixmap>
#include<QDebug>
#include<QString>
#include<QTimer>//定时器
#include<QLCDNumber>
#include <QFile>
#include<QIODevice>
#include<QTextStream>
#include<QByteArray>
#include<QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QLegend>
#include <QBarCategoryAxis>
QT_CHARTS_USE_NAMESPACE

//设置全局时间
 int global_time=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setMaximum(1000);//调整滑条的最大值
    connect(ui->pushButton_23,&QPushButton::clicked,this,&MainWindow::close);

    //初始加载当前所有猪的信息
   allpig.setFileName("../allpig.text");
   allpig.open(QIODevice::WriteOnly);
   QTextStream out4(&allpig);
   out4<<QString("猪圈号 ")<<QString("猪编号   ")<<QString("猪种类  ")<<QString("猪重量  ")
     <<QString("猪培育时间   ")<<"\n";
   allpig.close();
   allpig.open(QIODevice::ReadOnly);
   QTextStream out6(&allpig);
   QString str2=out6.readAll();
   ui->textEdit->setText(str2.toUtf8().data());
   allpig.close();

    //设置保存猪的信息的文件
     salelog.setFileName("../pig_salelog.txt");
     buylog.setFileName("../pig_buylog.text");
     salelog.open(QIODevice::WriteOnly);

             QTextStream out(&salelog);

            out <<QString("出圈时间         ") <<QString("猪圈号        ")<<QString("出圈总数量     ") <<QString("销售总金额   ") << "\n";
            salelog.close() ;
     buylog.open(QIODevice::WriteOnly);
             QTextStream out3(&buylog);

             out3<<QString("入圈时间         ") <<QString("黑猪数量        ")<<QString("小花猪数量    ")
                <<QString("大花白猪数量  ") << "\n";
                   buylog.close();


     bool timestatus=1;//时间状态
    //设置定时器
    QTimer*clock=new QTimer(this);
    connect(clock,&QTimer::timeout,
            [=]{
        global_time+=1;
        ui->lcdNumber->display(global_time);
        //猪长肉
        for(int i=0;i<100;i++){
            for(int j=0;j<ph[i].getsize();j++){
                ph[i].pg[j]->weightgrow();
            }
        }
        //三个月出栏一次
        double sale=0;
        if(global_time>=90&&global_time%90==0){
            for(int i=0;i<100;i++){
                sale+=ph[i].pigchange(&salelog,global_time,i);//出圈处理，同时统计售价
            }
        }

        if(sale!=0){
            qDebug()<<"出圈成功，出圈总售价为"<<sale<<"元";
            int add_num=10+rand()%10;
            addpig(add_num,1,global_time);
        }
    });

    connect(ui->pushButton_22,&QPushButton::released,
            [=,&timestatus]{
        if(timestatus){
            timestatus=0;
            clock->start(100);
            ui->pushButton_22->setText("停止计时");
        }
        else{
            timestatus=1;
            clock->stop();
            ui->pushButton_22->setText("开始计时");
        }
    }
            );


    //初始化猪圈编号0-99
    for(int i=0;i<100;i++){
        ph[i].setnum(i);
    }

    //添加猪
    srand((unsigned)time(NULL));
    connect(ui->pushButton,&QPushButton::clicked,
            [=]{
        int add_num=ui->spinBox->value();
       addpig(add_num,0,global_time);//构造初始的猪
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
     int t1=0,t2=0,t3=0,t4=0;
    for(int i=0;i<100;i++){
        s_black+=ph[i].getblack_num();
        s_xiaohua+=ph[i].getxiaohua_num();
        s_dahua+=ph[i].getdahua_num();
        for(int j=0;j<ph[i].getsize();j++){
            if(ph[i].pg[j]->getexistTime()<100)
                t1++;
            else if(ph[i].pg[j]->getexistTime()>=100&&ph[i].pg[j]->getexistTime()<200)
                t2++;
             else if(ph[i].pg[j]->getexistTime()>=200&&ph[i].pg[j]->getexistTime()<300)
                t3++;
            else if(ph[i].pg[j]->getexistTime()>=300)
                    t4++;

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

    ui->lineEdit_16->setText(QString::number(t1)+QString("头"));
    ui->lineEdit_17->setText(QString::number(t2)+QString("头"));
    ui->lineEdit_18->setText(QString::number(t3)+QString("头"));
    ui->lineEdit_19->setText(QString::number(t4)+QString("头"));


}

void MainWindow::addpig(int add_num,bool isin,int time){//添加猪函数
    qDebug()<<"猪的品种  "<<"猪的体重  "<<
              "猪的价格   "<<"猪所在圈数";
    int hei=0,xiao=0,da=0;
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
                     hei++;
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
                     if(a_kind==2)xiao++;
                     else da++;
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
    if(isin){
        buylog.open(QIODevice::ReadWrite|QIODevice::Append);
                QTextStream out2(&buylog);
              int month=time/30;
               out2 <<QString("第")<<month<<QString("个月          ") <<hei<<QString("头             ") <<
                xiao<<QString("头             ") << da<<QString("头")<<"\n";

               buylog.close() ;
    }
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



void MainWindow::on_pushButton_24_clicked()//切换页面
{
    int ncount=ui->stackedWidget->count();
    int nindex=ui->stackedWidget->currentIndex();
    //获取下一个页面索引
    ++nindex;

    // 当需要显示的页面索引大于等于总页面时，切换至首页
        if (nindex >=ncount)
            nindex = 0;
        ui->stackedWidget->setCurrentIndex(nindex);
}

void MainWindow::on_pushButton_25_clicked()
{
    int ncount=ui->stackedWidget->count();
    int nindex=ui->stackedWidget->currentIndex();
    //获取下一个页面索引
    ++nindex;
    // 当需要显示的页面索引大于等于总页面时，切换至首页
        if (nindex >= ncount)
            nindex = 0;
        ui->stackedWidget->setCurrentIndex(nindex);
}

void MainWindow::on_pushButton_26_clicked()//查询销售记录，将猪的信息从文件里读进文本编辑区
{
    salelog.open(QIODevice::ReadOnly);
    QTextStream stream(&salelog);
    QString str=stream.readAll();

    ui->textEdit->setText(str.toUtf8().data());
    salelog.close();
}

void MainWindow::on_pushButton_27_clicked()//查询购入记录，将猪的信息从文件里读进文本编辑区
{
    buylog.open(QIODevice::ReadOnly);
    QTextStream stream(&buylog);
    QString str=stream.readAll();

    ui->textEdit->setText(str.toUtf8().data());
    buylog.close();
}

void MainWindow::on_pushButton_28_clicked()
{

    allpig.open(QIODevice::WriteOnly);
    QTextStream out5(&allpig);
    out5<<QString("猪圈号 ")<<QString("猪编号   ")<<QString("猪种类  ")<<QString("猪重量  ")
      <<QString("猪培育时间   ")<<"\n";
    for(int i=0;i<100;i++){
        for(int j=0;j<ph[i].getsize();j++){
            out5<<i<<"      "<<j<<"  ";
            if(ph[i].pg[j]->getkind()==1)
            out5<<QString("    黑猪    ");
             else if(ph[i].pg[j]->getkind()==2)
            out5<<QString("    小花猪    ") ;
             else if(ph[i].pg[j]->getkind()==3)
                out5<<QString("    大花白猪    ");
            out5<<ph[i].pg[j]->getweight()<<"kg       ";
            out5<<ph[i].pg[j]->getexistTime();
            out5<<"\n";
        }
    }
    allpig.close();
    allpig.open(QIODevice::ReadOnly);
    QTextStream out7(&allpig);
    QString str3=out7.readAll();
    ui->textEdit->setText(str3.toUtf8().data());
    allpig.close();
}

//此函数用于猪瘟模拟
void MainWindow::on_pushButton_32_clicked()

{  //先将所有的猪的状态恢复至未感染状态
    for(int i=0;i<100;i++){
        for(int j=0;j<ph[i].getsize();j++){
            ph[i].setvirus(0);
            ph[i].pg[j]->setisill(0);
}}

       int overtime=0;
      int house=ui->spinBox_5->value();
      int pignum=ui->spinBox_6->value();
       int sign=1;//sign用于记录是否所有的猪圈里都有猪，每个猪圈都有猪才有可能全部感染
       for(int i=0;i<100;i++){
           if(ph[i].getsize()==0){
               sign=0;break;
           }
       }
      //先判断初始感染的猪是否存在
      if(pignum<ph[house].getsize()&&pignum>=0){
          ph[house].pg[pignum]->setisill(true);//初始感染的猪
          ph[house].setvirus(1);
          if(sign){

             //构造循环感染，循环内判断，若所有猪均被感染，则退出循环
             while(1){
                 overtime++;
                 for(int i=0;i<100;i++){
                    int flag=ph[i].getvirus(); //找出某一个猪圈是否有猪感染
                      //若有猪感染，则对相邻猪圈和当前猪圈进行一轮感染
                     if(flag){
                         for(int k=0;k<ph[i].getsize();k++){
                             //对没感染的猪才进行感染
                             if(ph[i].pg[k]->getisill()==false){

                             int t=rand()%2;//50%的几率感染
                             if(t==0){
                                 ph[i].pg[k]->setisill(true);
                                 ph[i].setvirus(1);
                         }
                     }
                         }
                         if(i+1<=99){
                             for(int k=0;k<ph[i+1].getsize();k++){
                                 if(ph[i+1].pg[k]->getisill()==false){
                                     int t=rand()%100;
                                     if(t<=14){
                                         ph[i+1].setvirus(1);
                                         ph[i+1].pg[k]->setisill(true);
                                 }
                             }
                         }
                         }
                        if(i-1>=0){
                            for(int k=0;k<ph[i-1].getsize();k++){
                                 if(ph[i-1].pg[k]->getisill()==false){
                                     int t=rand()%100;
                                     if(t<=14){
                                         ph[i-1].pg[k]->setisill(true);
                                         ph[i-1].setvirus(1);
                                     }
                                     }

                                                   }
                                               }
                        }


             }

                int isbreak=1;
                 //判断是否所有的猪均已被感染
                     for(int i=0;i<100;i++){
                         if(isbreak==0)
                             break;

                         for(int j=0;j<ph[i].getsize();j++){
                             if(ph[i].pg[j]->getisill()==false){
                                 isbreak=0;
                                 break;
                             }

                         }
                     }
                     if(isbreak)
                         break;
     }
           ui->lineEdit_15->setText(QString::number (overtime)+QString("天") );
          }
          else{
              ui->lineEdit_15->setText(QString("有空猪圈，不可能全部感染") );
          }

          }
      else{
         ui->lineEdit_15->setText( QString("此猪不存在，请重新输入:"));
      }
      }


void MainWindow::on_pushButton_35_clicked()
{
    int ncount=ui->stackedWidget->count();
    int nindex=ui->stackedWidget->currentIndex();
    //获取下一个页面索引
    ++nindex;
    // 当需要显示的页面索引大于等于总页面时，切换至首页
        if (nindex >= ncount)
            nindex = 0;
        ui->stackedWidget->setCurrentIndex(nindex);
}

//此函数用于猪瘟发病后的隔离
void MainWindow::on_pushButton_36_clicked()
{  //实现方法，若发现某猪圈有猪瘟，就把其相伶两个猪圈的猪踢出猪圈，实现隔离
    for(int i=0;i<100;i++){
        if(ph[i].getvirus()){
            if(i-1>=0){
                for(int j=0;j<ph[i-1].getsize();j++){
                    ph[i-1].pg.removeAt(j);
                    ph[i-1].setsize(0);
                    ph[i-1].setvirus(0);
                }
            }
            if(i+1<+99){
                for(int j=0;j<ph[i+1].getsize();j++){
                    ph[i+1].pg.removeAt(j);
                    ph[i+1].setsize(0);
                    ph[i+1].setvirus(0);
                }
            }
        }
    }
}

//显示数量分布图函数
void MainWindow::on_pushButton_42_clicked()
{
    QBarSet *set = new QBarSet(QString("number") );

    int black=0,xiao=0,da=0;
    for(int i=0;i<100;i++){
        black+=ph[i].getblack_num();
        xiao+=ph[i].getxiaohua_num();
        da+=ph[i].getdahua_num();
    }

    *set << black<<xiao<<da;
    QBarSeries *series = new QBarSeries();
    series->append(set);




    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("不同种类猪的数量分布图");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    QStringList categories;
    categories << "黑猪" << "小花猪" << "大花白猪";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();//创建默认的左侧的坐标轴（根据 QBarSet 设置的值）
    chart->setAxisX(axis, series);//设置坐标轴



    chart->legend()->setVisible(true); //设置图例为显示状态
    chart->legend()->setAlignment(Qt::AlignBottom);//设置图例的显示位置在底部

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


        window.setCentralWidget(chartView);  //注意，显示窗口不要在函数内部定义
        //这样window变量是局部变量，栈里分配，运行完就撤销，会出现闪退
        //解决方法，将窗口变量定义为当前类的成员
        window.resize(600, 400);
        window.show();

}

//显示体重分布函数图
void MainWindow::on_pushButton_43_clicked()
{
    QBarSet *set = new QBarSet(QString("weight") );

    int w1=0,w2=0,w3=0,w4=0;
    for(int i=0;i<100;i++){
        for(int j=0;j<ph[i].getsize();j++){
            if(ph[i].pg[j]->getweight()<50)
                w1++;
            else if(ph[i].pg[j]->getweight()>=50&&ph[i].pg[j]->getweight()<80)
                w2++;
            else if(ph[i].pg[j]->getweight()>=80&&ph[i].pg[j]->getweight()<120)
                w3++;
            else  w4++;

        }

    }

    *set << w1<<w2<<w3<<w4;
    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("不同种类猪的重量分布图");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    QStringList categories;
    categories << "0~50kg" << "50~80kg" << "80~120kg"<<"120~150kg";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();//创建默认的左侧的坐标轴（根据 QBarSet 设置的值）
    chart->setAxisX(axis, series);//设置坐标轴



    chart->legend()->setVisible(true); //设置图例为显示状态
    chart->legend()->setAlignment(Qt::AlignBottom);//设置图例的显示位置在底部

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


       window.setCentralWidget(chartView);
        window.resize(600, 400);
        window.show();
}

void MainWindow::on_pushButton_44_clicked()
{
    QBarSet *set = new QBarSet(QString("raiseTime") );

    int d1=0,d2=0,d3=0,d4=0;
    for(int i=0;i<100;i++){
        for(int j=0;j<ph[i].getsize();j++){
            if(ph[i].pg[j]->getweight()<100)
                d1++;
            else if(ph[i].pg[j]->getweight()>=100&&ph[i].pg[j]->getweight()<200)
                d2++;
            else if(ph[i].pg[j]->getweight()>=200&&ph[i].pg[j]->getweight()<300)
                d3++;
            else  d4++;

        }

    }

    *set << d1<<d2<<d3<<d4;
    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("不同种类猪的饲养时间分布图");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    QStringList categories;
    categories << "0~100天" << "100~200天" << "200~300天"<<"300天以上";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);



    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


       window.setCentralWidget(chartView);
        window.resize(600, 400);
        window.show();
}
