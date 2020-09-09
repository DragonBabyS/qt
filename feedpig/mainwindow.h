#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pig.h"
#include"pighouse.h"
#include<QDebug>
#include<QFile>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //pig pigs[100];
    Pighouse ph[100];//猪圈
     QFile salelog;//存储销售记录的文件
     QFile buylog;//存储购入记录的文件
     QFile allpig;//存贮当前所有猪信息的文件
     QMainWindow window;//显示住的数量分布
     void searchpighouse();//查询猪圈里的猪的信息
    void searchonepig();//查询单只猪的信息
    void sum();//统计整个猪场每个品种猪的数量和体重、饲养时间分布情况
    void addpig(int add_num,bool isin,int time);//出圈后新进一批猪
private:
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent*e);

private slots:

    void on_pushButton_24_clicked();
    void on_pushButton_25_clicked();
    void on_pushButton_26_clicked();
    void on_pushButton_27_clicked();
    void on_pushButton_28_clicked();
    void on_pushButton_32_clicked();
    void on_pushButton_35_clicked();
    void on_pushButton_36_clicked();
    void on_pushButton_42_clicked();

    void on_pushButton_43_clicked();
    void on_pushButton_44_clicked();
};

#endif // MAINWINDOW_H
