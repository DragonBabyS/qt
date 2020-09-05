#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pig.h"
#include"pighouse.h"

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

    void searchpighouse();//查询猪圈里的猪的信息
    void searchonepig();//查询单只猪的信息
    void sum();//统计整个猪场每个品种猪的数量和体重、饲养时间分布情况
private:
    Ui::MainWindow *ui;
protected:
    void paintEvent(QPaintEvent*e);

};

#endif // MAINWINDOW_H
