#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lushilogic.h"
#include <QPainter>
#include <qtimer.h>
#include<QPoint>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QSlider>
#include <QMediaPlaylist>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    lushilogic *game;

    QPixmap b;
    QPainter a[30];
    QPainter c[30];
    QPainter background_1;
    QPainter background_2;
    QPainter d[30];
    QPainter f[30];
    QPainter weilan,energy_one[10],energy_two[10];
    QPainter end_round;
    QPainter blood_1[7],blood_2[7];
    QPainter attack_1[7],attack_2[7];
    QPainter hunter_weapeon,warrior_weapeon;
    QPainter shield;
    QPainter green;
    QPainter hunter_blood,warrior_blood;
    QPainter resistant,weapeon_max_attack,jiantou;
    QMainWindow *window;
    QMediaPlayer*player;
    QMediaPlayer*movie;
    QVideoWidget*videoWidget;
    QMainWindow*victory;
    QMainWindow*lose;
    QMediaPlaylist*playlist;


    std::vector<card>med;
    std::vector<card>med_2;

    int card_exist_clicked=0;    //判断所有手牌中是否有被点的
    int current_location;
    int move_x,move_y;
    int last_x,last_y;//自动退回
    int attacker_x=-1,attacker_y=-1;
    int begin_number=-1,end_number=-1,timecount=0;
    bool begin=false;
    int attack_hero=0;
    int attack_hero_from=-1;

    void put_picure(QPixmap &b,int c);
    void put_picure_(QPixmap &b,int c);
    void put_picure_hero(QPixmap &b,int c);
    void judge_blood(QPixmap &b,int c);
    void judge_attack(QPixmap &b,int c);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void deal_attack_hunter();
    void deal_attack_warrior();


    QTimer *clock;

private:
    Ui::MainWindow *ui;




protected:

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // MAINWINDOW_H
