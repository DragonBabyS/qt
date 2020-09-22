#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
//#include <Qtime>
#include <time.h>
#include<QTimer>
#include<QPoint>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QSlider>
#include<QPixmap>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QDialog>
#include<QMessageBox>
#include<QIcon>
#include<QFont>
#include<QtWidgets/QMainWindow>
#include <QMediaPlaylist>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    resize(1800,1000);
    game=new lushilogic;
    clock=new QTimer(this);
    connect(clock,&QTimer::timeout,[=](){
    update();
    timecount++;
    });
    clock->start(5);

    this->setMouseTracking(true);

    this->centralWidget()->setMouseTracking(true);
    this->setWindowIcon(QIcon("://图层5.png"));



       ui->pushButton_4->setStyleSheet("border-image:url(://图层 9.png)");
       ui->pushButton->setStyleSheet("border-image:url(://图层6.png)");
       ui->pushButton_3->setStyleSheet("border-image:url(://图层 4.png)");


       ui->horizontalSlider->setStyleSheet(
                   //设置滑动条无边框
                   "QSlider{border:none; background-color:transparent;border-radius: 8px; } "
                   //设置小滑块样式为透明
                   "QSlider::handle:horizontal {    background: transparent;"
                   "border: none;"
                  "width: 12px;"
                  "height: 6px; "
                   "border-radius: 3px;} "//圆滑度


                   //设置滑条
                  " QSlider::groove:horizontal{ background-color:#ffffff;border-radius: 8px;}  "



                   //设置滑块未滑过部分
                   "QSlider::add-page:horizontal { border-radius :3px;background: #ffffff; } "



                   //设置滑块已滑过部分
                   "QSlider::sub-page:horizontal { border-radius :3px; background-color:blue;  } "

                                          );
        ui->horizontalSlider->setMaximum(200);
        ui->horizontalSlider->setMinimum(0);
        connect(ui->pushButton,&QPushButton::clicked,
                 [=]{
               ui->stackedWidget->setCurrentIndex(2);
         }
             );

         QMenuBar*bar=menuBar();
         setMenuBar(bar);
         QMenu*menu=bar->addMenu("主菜单");

         QMenu*menu2=bar->addMenu("音量调节");
         QMenu*menu3=bar->addMenu("宣传片");
         QAction*p4=menu3->addAction("播放");
         connect(p4,&QAction::triggered,[=]{
             movie->setMedia(QUrl::fromLocalFile("D:/music/宣传片.wav"));
                  movie->setVolume(30);
                    movie->play();


                       player->setMedia(QUrl::fromLocalFile("D:/music/炉石视频.wmv"));

                                   window=new QMainWindow;
                                   videoWidget = new QVideoWidget(window);
                                 window->setCentralWidget(videoWidget);
                                   videoWidget->resize(800,600);
                                  player->setVideoOutput(videoWidget);
                                   videoWidget->show();
                                   window->show();
                                   window->resize(800,600);
                                  player->play();
         });
         QAction*p1=menu->addAction("退出");
         connect(p1,&QAction::triggered,
                 [=]{
           int ret=QMessageBox::question(this,"exit","是否退出游戏");
           switch(ret){
           case QMessageBox::Yes:
                  close();
               break;
           case QMessageBox::No:
                   break;
           }
         }
                 );
         QAction*p2=menu2->addAction("up");
         QAction*p3=menu2->addAction("down");
         connect(p2,&QAction::triggered,[=]{
             movie->setVolume(movie->volume()+30);
         });
         connect(p3,&QAction::triggered,[=]{
             movie->setVolume(movie->volume()-30);
         });
         connect(ui->horizontalSlider, &QSlider::valueChanged,[=]{
             int x=ui->horizontalSlider->value();
             movie->setVolume(x);

         });
    //设置音频和视频播放器
          player = new QMediaPlayer;
          movie=new QMediaPlayer;


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    int i=ev->x();
    int j=ev->y();
    if(j>=300&&j<=450&&i<1350)   //800值待定
    {
        if(game->current_side==0&&game->emit_locked==0&&card_exist_clicked==1&&med[0].type==person&&game->attacker==-1)
        {
            //猎人放置随从
            bool clicked_2=false;
            for(int k=0;k<game->card_battle_visiable_1.size();k++)
            {
                if(i>=920-65*game->card_battle_visiable_1.size()+130*k+100&&i<=920-65*game->card_battle_visiable_1.size()+130*(k+1))
                {
                    game->card_battle_visiable_1.insert(game->card_battle_visiable_1.begin()+1+k,med[0]);
                    clicked_2=true;
                    current_location=k+1;
                    break;
                }
            }
            if(i>=920-65*game->card_battle_visiable_1.size()+130*game->card_battle_visiable_1.size())
            {
                current_location=game->card_battle_visiable_1.size();
                game->card_battle_visiable_1.push_back(med[0]);
                clicked_2=true;
            }
            if(i<=920-65*game->card_battle_visiable_1.size())
            {
                current_location=0;
                game->card_battle_visiable_1.insert(game->card_battle_visiable_1.begin(),med[0]);
                clicked_2=true;
            }
            if(clicked_2)
            {
                for(int k=0;k<game->card_hand_1.size();k++)
                {
                    if(game->card_hand_1[k].clicked==true)
                    {
                        game->energy_1=game->energy_1-game->card_hand_1[k].cost;
                        game->card_hand_1.erase(game->card_hand_1.begin()+k);
                        game->deal_shout(med[0],current_location);
                        update();
                        game->attack_status_change();
                        if(med[0].which!=3&&med[0].zhongzu==beast)
                            game->card_battle_visiable_1[current_location].attack+=game->forest_wolf();
                        else if(med[0].which==3&&med[0].zhongzu==beast)
                            game->card_battle_visiable_1[current_location].attack+=game->forest_wolf()-1;
                        if(med[0].which==3)
                            for(int i=0;i<game->card_battle_visiable_1.size();i++)
                                if(i!=current_location&&game->card_battle_visiable_1[i].zhongzu==beast)
                                    game->card_battle_visiable_1[i].attack++;
                        med.clear();
                        card_exist_clicked=0;
                        break;
                    }
                }
            }
            update();
        }
        if((game->emit_locked==0&&card_exist_clicked==0&&game->card_battle_visiable_1.size()!=0&&game->hero_attack)||
                (game->emit_locked==0&&card_exist_clicked==0&&game->card_battle_visiable_1.size()!=0)||
                (game->emit_locked!=0&&card_exist_clicked==0&&game->attacker==-1))

        {
            bool clicked_2=false;
            for(int k=0;k<game->card_battle_visiable_1.size();k++)
            {
                if(i>=920-65*game->card_battle_visiable_1.size()+130*k&&i<=920-65*game->card_battle_visiable_1.size()+130*k+100)
                {
                    clicked_2=true;
                    current_location=k;
                    break;
                }
            }
            if(game->emit_locked==0&&card_exist_clicked==0&&game->card_battle_visiable_1.size()!=0&&game->hero_attack)
            {
                //战士脸打随从
                game->kuangzhnashi_add(1);
                attacker_x=-1;
                attacker_y=-1;
                game->card_battle_visiable_1[current_location].blood-=game->warrior.attack_max;
                game->warrior.blood-=game->card_battle_visiable_1[current_location].attack;
                update();
                game->warrior.useable_times_current--;
                if(!game->warrior.useable_times_current)
                {
                    game->warrior.weapeon=null_weapeon;
                    game->warrior.attack_max=0;
                    game->warrior.useable_times_current=0;
                    game->warrior.attack_base=0;
                    game->warrior.useable_times_max=0;
                    game->warrior.useable_times_base=0;
                }
                game->hero_attack=false;
                if(game->card_battle_visiable_1[current_location].blood<1)
                {
                    game->forest_wolf_die(game->card_battle_visiable_1[current_location]);
                    game->deal_dietalking(game->card_battle_visiable_1[current_location]);
                    game->card_battle_visiable_1.erase(game->card_battle_visiable_1.begin()+current_location);
                    if(game->card_battle_visiable_1[current_location].zhongzu==beast)
                        game->tulang_add();
                }
                if(game->warrior.blood<1)
                {
                    //输
                    lose=new QMainWindow;
                    lose->setStyleSheet("border-image:url(://微信截图_20200916160830.png)");
                    lose->show();
                    lose->setWindowState(Qt::WindowMaximized);
                }
            }


            else if(game->emit_locked==0&&card_exist_clicked==0&&game->card_battle_visiable_1.size()!=0)
            {
                //随从换血
                if(game->current_side==1&&game->attacker!=-1)
                {
                    game->defender=current_location;
                    //game->deal_attack(game->current_side,game->attacker,game->defender);    //搞完记得变-1

                    begin=true;
                    begin_number=game->attacker;
                    end_number=game->defender;
                    timecount=0;

                    game->attacker=-1;game->defender=-1;


                    attacker_x=-1;attacker_y=-1;
                    update();
                }
            }

            else if(game->emit_locked!=0&&card_exist_clicked==0&&game->attacker==-1)
            {
                if(clicked_2)
                {
                    if(game->emit_locked==4||game->emit_locked==7)
                    {
                        game->kuangzhnashi_add(1);
                        game->card_battle_visiable_1[current_location].blood=game->card_battle_visiable_1[current_location].blood-game->magic_killing_force;
                        game->magic_killing_force=0;
                        if(game->card_battle_visiable_1[current_location].blood<=0)
                        {
                            game->forest_wolf_die(game->card_battle_visiable_1[current_location]);
                            game->deal_dietalking(game->card_battle_visiable_1[current_location]);
                            game->card_battle_visiable_1.erase(game->card_battle_visiable_1.begin()+current_location);
                        }
                        game->emit_locked=0;
                    }
                    attacker_x=-1;
                    attacker_y=-1;
                }
                update();
            }
        }

    }


    if(j>=500&&j<=650&&i<=1350)   //800值待定
    {
       if(game->current_side==1&&game->emit_locked==0&&card_exist_clicked==1&&med[0].type==person&&game->attacker==-1)
        {
            //战士放随从
            bool clicked_2=false;
            for(int k=0;k<game->card_battle_visiable_2.size();k++)
            {
                if(i>=920-65*game->card_battle_visiable_2.size()+130*k+100&&i<=920-65*game->card_battle_visiable_2.size()+130*(k+1))
                {
                    game->card_battle_visiable_2.insert(game->card_battle_visiable_2.begin()+1+k,med[0]);
                    clicked_2=true;
                    current_location=k+1;
                    break;
                }
            }
            if(i>=920-65*game->card_battle_visiable_2.size()+130*game->card_battle_visiable_2.size())
            {
                current_location=game->card_battle_visiable_2.size();
                game->card_battle_visiable_2.push_back(med[0]);
                clicked_2=true;
            }
            else if(i<=920-65*game->card_battle_visiable_2.size())
            {
                current_location=0;
                game->card_battle_visiable_2.insert(game->card_battle_visiable_2.begin(),med[0]);
                clicked_2=true;
            }
            update();
            if(clicked_2)
            {
                for(int k=0;k<game->card_hand_2.size();k++)
                {
                    if(game->card_hand_2[k].clicked==true)
                    {

                        game->energy_2=game->energy_2-game->card_hand_2[k].cost;
                        game->card_hand_2.erase(game->card_hand_2.begin()+k);
                        game->deal_shout(med[0],current_location);
                        game->warrior_runrun(current_location);
                        game->call_paqisi(med[0]);
                        if(med[0].which!=35&&med[0].zhongzu==pirate)
                        {
                            game->card_battle_visiable_2[current_location].attack+=game->captain();
                            game->card_battle_visiable_2[current_location].blood+=game->captain();
                        }
                        else if(med[0].which==35&&med[0].zhongzu==pirate)
                        {
                            game->card_battle_visiable_2[current_location].attack+=game->captain()-1;
                            game->card_battle_visiable_2[current_location].blood+=game->captain()-1;
                        }
                        if(med[0].which==35)
                        {
                            for(int i=0;i<game->card_battle_visiable_2.size();i++)
                            {
                                if(i!=current_location&&game->card_battle_visiable_2[i].zhongzu==pirate)
                                {
                                    game->card_battle_visiable_2[i].attack++;
                                    game->card_battle_visiable_2[i].blood++;
                                }
                            }
                        }
                        update();
                        med.clear();
                        card_exist_clicked=0;
                        break;
                    }
                }
            }
        }
        if((game->emit_locked==0&&card_exist_clicked==0&&game->card_battle_visiable_2.size()!=0&&game->hero_attack)||
                (game->emit_locked==0&&card_exist_clicked==0&&game->card_battle_visiable_2.size()!=0)||
                (game->emit_locked!=0&&card_exist_clicked==0))
        {
            bool clicked_2=false;
            for(int k=0;k<game->card_battle_visiable_2.size();k++)
            {
                if(i>=920-65*game->card_battle_visiable_2.size()+130*k&&i<=920-65*game->card_battle_visiable_2.size()+130*k+100)
                {
                    clicked_2=true;
                    current_location=k;
                    break;

                }
            }
            if(game->emit_locked==0&&card_exist_clicked==0&&game->card_battle_visiable_2.size()!=0&&game->hero_attack)
            {
                game->kuangzhnashi_add(1);
                attacker_x=-1;
                attacker_y=-1;
                game->card_battle_visiable_2[current_location].blood-=game->hunter.attack_max;
                game->hunter.blood-=game->card_battle_visiable_2[current_location].attack;
                game->hunter.useable_times_current--;
                if(!game->hunter.useable_times_current)
                {
                    game->hunter.weapeon=null_weapeon;
                    game->hunter.attack_max=0;
                    game->hunter.useable_times_current=0;
                    game->hunter.attack_base=0;
                    game->hunter.useable_times_max=0;
                    game->hunter.useable_times_base=0;
                }
                game->hero_attack=false;
                if(game->card_battle_visiable_2[current_location].blood<1)
                    game->card_battle_visiable_2.erase(game->card_battle_visiable_2.begin()+current_location);

                if(game->hunter.blood<1)
                {
                    //赢
                    victory=new QMainWindow;
                       victory->setStyleSheet("border-image:url(://微信截图_20200916161401.png)");
                       victory->show();
                       victory->setWindowState(Qt::WindowMaximized);
                }
            }

            else if(game->emit_locked==0&&card_exist_clicked==0&&game->card_battle_visiable_2.size()!=0)
            {
                if(game->current_side==0&&game->attacker!=-1)
                {
                    game->defender=current_location;
                    //game->deal_attack(game->current_side,game->attacker,game->defender);    //搞完记得变-1
                    begin=true;
                    begin_number=game->attacker;
                    end_number=game->defender;
                    timecount=0;


                    game->attacker=-1;game->defender=-1;




                    attacker_x=-1;attacker_y=-1;
                    update();
                }
            }


            if(game->emit_locked!=0&&card_exist_clicked==0)
            {
                if(clicked_2)
                {
                    if(game->emit_locked==4||game->emit_locked==7)
                    {
                        game->kuangzhnashi_add(1);
                        game->card_battle_visiable_2[current_location].blood=game->card_battle_visiable_2[current_location].blood-game->magic_killing_force;
                            game->magic_killing_force=0;
                        if(game->card_battle_visiable_2[current_location].blood<=0)
                        {
                            game->forest_wolf_die(game->card_battle_visiable_2[current_location]);
                            game->deal_dietalking(game->card_battle_visiable_2[current_location]);
                            game->card_battle_visiable_2.erase(game->card_battle_visiable_2.begin()+current_location);
                            if(game->card_battle_visiable_2[current_location].zhongzu==beast)
                                game->tulang_add();
                        }
                        game->emit_locked=0;
                    }
                    attacker_x=-1;
                    attacker_y=-1;
                }

                update();
            }
        }
    }


    if(i>=830&&i<=970&&j>=160&&j<=260)
    {

        if(game->current_side==1&&game->hero_attack)
        {
            attacker_x=-1;
            attacker_y=-1;
            game->hunter.blood-=game->warrior.attack_max;
            game->hero_attack=false;
            game->warrior.useable_times_current--;
            if(!game->warrior.useable_times_current)
            {
                game->warrior.weapeon=null_weapeon;
                game->warrior.attack_max=0;
                game->warrior.useable_times_current=0;
                game->warrior.attack_base=0;
                game->warrior.useable_times_max=0;
                game->warrior.useable_times_base=0;
            }
        }
        else if(game->current_side==1&&game->attacker!=-1)
        {
            attacker_x=-1;
            attacker_y=-1;
            attack_hero=1;
            timecount=0;
            attack_hero_from=game->attacker;
        }
        else if((game->emit_locked==4||game->emit_locked==7)&&card_exist_clicked==0)
        {
            game->hunter.blood-=game->magic_killing_force;
            game->emit_locked=0;
            attacker_x=-1;
            attacker_y=-1;
        }
        if(game->hunter.blood<1)
        {
            //赢
            victory=new QMainWindow;
                                  victory->setStyleSheet("border-image:url(://微信截图_20200916161401.png)");
                                  victory->show();
                                  victory->setWindowState(Qt::WindowMaximized);
        }

    }

    if(i>=830&&i<=970&&j>=720&&j<=845)    //战士
    {

        if(game->current_side==0&&game->hero_attack)
        {
            attacker_x=-1;
            attacker_y=-1;
            game->warrior.blood-=game->hunter.attack_max;
            game->hero_attack=false;
            game->hunter.useable_times_current--;
            if(!game->hunter.useable_times_current)
            {
                game->hunter.weapeon=null_weapeon;
                game->hunter.attack_max=0;
                game->hunter.useable_times_current=0;
                game->hunter.attack_base=0;
                game->hunter.useable_times_max=0;
                game->hunter.useable_times_base=0;
            }
        }
        else if(game->current_side==0&&game->attacker!=-1)
        {
            attacker_x=-1;
            attacker_y=-1;
            attack_hero=2;
            timecount=0;
            attack_hero_from=game->attacker;
        }
        else if((game->emit_locked==4||game->emit_locked==7)&&card_exist_clicked==0)
        {
            game->warrior.blood-=game->magic_killing_force;
            game->emit_locked=0;
            attacker_x=-1;
            attacker_y=-1;
        }

        if(game->warrior.blood<1)
        {
            //输
            lose=new QMainWindow;
                                lose->setStyleSheet("border-image:url(://微信截图_20200916160830.png)");
                                lose->show();
                                lose->setWindowState(Qt::WindowMaximized);

        }
    }

    update();

}


void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    int i=ev->x();
    int j=ev->y();
    /*
     * 猎人手牌
     */
    //qDebug("%d  %d",i,j);
    if(i>=870-25*game->card_hand_1.size()&&i<=870-25*game->card_hand_1.size()+50*(game->card_hand_1.size()-1)+100&&j>=0&&j<=150&&game->emit_locked==0)
    {
        game->number=(i-870+25*game->card_hand_1.size())/50;
        if(game->number>game->card_hand_1.size()-1)
            game->number=game->card_hand_1.size()-1;
        if(game->current_side==0)
        {
            if(game->card_hand_1[game->number].clicked==false&&card_exist_clicked==0&&game->card_hand_1[game->number].cost<=game->energy_1)
            {
                game->card_hand_1[game->number].clicked=true;
                med.push_back(game->card_hand_1[game->number]);
                card_exist_clicked++;
                if(game->card_hand_1[game->number].which==10)
                {
                    game->energy_1=game->energy_1-game->card_hand_1[game->number].cost;
                    game->hunter.weapeon=game->card_hand_1[game->number].weapeon;
                    game->hunter.attack_max=3;
                    game->hunter.attack_base=3;
                    game->hunter.useable_times_max=2;
                    game->hunter.useable_times_current=2;
                    game->hunter.useable_times_base=2;
                    game->card_hand_1.erase(game->card_hand_1.begin()+game->number);
                    card_exist_clicked=0;
                    med.clear();
                }
                if(game->card_hand_1[game->number].type==magic)
                {
                    game->energy_1=game->energy_1-game->card_hand_1[game->number].cost;
                    if(game->card_hand_1[game->number].magical==hunter_tip)
                    game->emit_locked=1;
                    else if(game->card_hand_1[game->number].magical==tracking)
                    {
                        //buhui
                    }
                    else if(game->card_hand_1[game->number].magical==dog_dog)
                    {
                        while(game->card_battle_visiable_1.size()<game->card_battle_visiable_2.size())
                            game->card_battle_visiable_1.push_back(game->card_extended[2]);

                    }
                    else if(game->card_hand_1[game->number].magical==animal_friend)
                    {
                       srand(unsigned(time(nullptr)));
                       int index = qrand()%3;
                       if(game->card_battle_visiable_1.size()<7)
                           game->card_battle_visiable_1.push_back(game->card_extended[3+index]);
                    }
                    else if(game->card_hand_1[game->number].magical==killing_order)
                    {
                        if(game->beast_exist())
                            game->magic_killing_force=5;
                        else {
                            game->magic_killing_force=3;
                        }
                        game->emit_locked=4;
                        attacker_x=i;
                        attacker_y=j;
                    }
                    else if(game->card_hand_1[game->number].magical==killed_shotting&&game->card_battle_visiable_2.size()!=0)
                    {
                        srand(unsigned(time(nullptr)));
                        int index = qrand()%static_cast<int>(game->card_battle_visiable_2.size());
                        game->deal_dietalking(game->card_battle_visiable_2[index]);
                        game->captain_die(game->card_battle_visiable_2[index]);
                        game->card_battle_visiable_2.erase(game->card_battle_visiable_2.begin()+index);
                    }
                    game->card_hand_1.erase(game->card_hand_1.begin()+game->number);
                    card_exist_clicked=0;
                    med.clear();
                }

            }
            else if(game->card_hand_1[game->number].clicked==true&&card_exist_clicked==1)
            {
                game->card_hand_1[game->number].clicked=false;
                med.clear();
                 card_exist_clicked--;
            }

        }

        update();
    }





   /*
    * 战士手牌
    */

    if(i>=870-25*game->card_hand_2.size()&&i<=870-25*game->card_hand_2.size()+50*(game->card_hand_2.size()-1)+100&&j>=850&&j<=1000&&game->emit_locked==0)
    {
        game->number=(i-870+25*game->card_hand_2.size())/50;
        if(game->number>game->card_hand_2.size()-1)
            game->number=game->card_hand_2.size()-1;
        if(game->current_side==1)
        {
            if(game->card_hand_2[game->number].which==39&&game->warrior.weapeon!=0)
                game->card_hand_2[game->number].cost=game->card_hand_2[game->number].cost-game->warrior.attack_max;
            if(game->card_hand_2[game->number].cost<0)
                game->card_hand_2[game->number].cost=0;
            if(game->card_hand_2[game->number].clicked==false&&card_exist_clicked==0&&game->card_hand_2[game->number].cost<=game->energy_2)
            {
                game->card_hand_2[game->number].clicked=true;
                med.push_back(game->card_hand_2[game->number]);
                card_exist_clicked++;
                if(game->card_hand_2[game->number].type==weapeon)
                {
                    game->chuangong_weapeon();
                    update();
                    game->energy_2=game->energy_2-game->card_hand_2[game->number].cost;
                    if(game->card_hand_2[game->number].weapeon==fire_fu)
                    {
                        game->warrior.weapeon=game->card_hand_2[game->number].weapeon;
                        game->warrior.attack_max=3;
                        game->warrior.attack_base=3;
                        game->warrior.useable_times_max=2;
                        game->warrior.useable_times_current=2;
                        game->warrior.useable_times_base=2;
                    }
                    else if(game->card_hand_2[game->number].weapeon==aojin_fu)
                    {
                        game->warrior.weapeon=game->card_hand_2[game->number].weapeon;
                        game->warrior.attack_max=5;
                        game->warrior.attack_base=5;
                        game->warrior.useable_times_max=2;
                        game->warrior.useable_times_current=2;
                        game->warrior.useable_times_base=2;
                    }
                    game->card_hand_2.erase(game->card_hand_2.begin()+game->number);
                    card_exist_clicked=0;
                    med.clear();
                }
                if(game->card_hand_2[game->number].type==magic)
                {
                    game->energy_2=game->energy_2-game->card_hand_2[game->number].cost;
                    if(game->card_hand_2[game->number].magical==upgrade)
                    {
                        if(game->warrior.weapeon==0)
                        {
                            game->warrior.weapeon=game->card_extended[6].weapeon;
                            game->warrior.attack_max=1;
                            game->warrior.attack_base=1;
                            game->warrior.useable_times_max=3;
                            game->warrior.useable_times_current=3;
                            game->warrior.useable_times_base=3;
                        }
                        else {
                            game->warrior.attack_max++;
                            game->warrior.useable_times_max++;
                            game->warrior.useable_times_current++;
                        }
                    }
                    if(game->card_hand_2[game->number].magical==pirate_shotting)
                    {
                        if(game->warrior.blood<=12)
                            game->magic_killing_force=6;
                        else {
                            game->magic_killing_force=4;
                        }
                        game->emit_locked=7;
                        attacker_x=i;
                        attacker_y=j;
                    }
                    game->card_hand_2.erase(game->card_hand_2.begin()+game->number);
                    card_exist_clicked=0;
                    med.clear();
                }

            }
            else if(game->card_hand_2[game->number].clicked==true&&card_exist_clicked==1)
            {
                game->card_hand_2[game->number].clicked=false;
                med.clear();
                card_exist_clicked--;
            }
        }
        update();
    }


    /*
     * 猎人场上
     */


    if(j>=300&&j<=450&&i<1350)   //800值待定
    {
        //不改
        if(game->emit_locked!=0&&card_exist_clicked==0&&game->attacker==-1)
        {
            bool clicked_2=false;
            for(int k=0;k<game->card_battle_visiable_1.size();k++)
            {
                if(i>=920-65*game->card_battle_visiable_1.size()+130*k&&i<=920-65*game->card_battle_visiable_1.size()+130*k+100)
                {
                    clicked_2=true;
                    current_location=k;
                    break;
                }
            }

            if(clicked_2)
            {
                //指定对象
                switch(game->emit_locked)
                {
                case 1:game->card_battle_visiable_1[current_location].blood=1;
                    game->emit_locked=0;;
                    break;
                case 2:/*jinhua*/
                    game->emit_locked=0;
                    break;
                case 5:if(game->card_battle_visiable_1[current_location].zhongzu==beast)
                    {
                        game->card_battle_visiable_1[current_location].attack=game->card_battle_visiable_1[current_location].attack+2;
                        game->card_battle_visiable_1[current_location].blood=game->card_battle_visiable_1[current_location].blood+2;
                        game->card_battle_visiable_1[current_location].shield=true;
                        game->emit_locked=0;
                    }
                    break;
                case 6:game->person_clear( game->card_battle_visiable_1[current_location]);
                    game->emit_locked=0;
                    break;
                }
            }
            update();
        }




        else if(game->emit_locked==0&&card_exist_clicked==0&&game->card_battle_visiable_1.size()!=0)
        {
            bool clicked_2=false;
            for(int k=0;k<game->card_battle_visiable_1.size();k++)
            {
                if(i>=920-65*game->card_battle_visiable_1.size()+130*k&&i<=920-65*game->card_battle_visiable_1.size()+130*k+100)
                {
                    clicked_2=true;
                    current_location=k;
                    break;
                }
            }
            //攻击
            if(game->current_side==0&&game->card_battle_visiable_1[current_location].attack_status==un_attacked)
            {
                attacker_x=i;
                attacker_y=j;
                game->attacker=current_location;
            }
        }


    }
    /*
     * 战士场上
     */

    if(j>=500&&j<=650&&i<=1350)   //800值待定
    {

       if(game->emit_locked!=0&&card_exist_clicked==0)
       {
           bool clicked_2=false;
           for(int k=0;k<game->card_battle_visiable_2.size();k++)
           {
               if(i>=920-65*game->card_battle_visiable_2.size()+130*k&&i<=920-65*game->card_battle_visiable_2.size()+130*k+100)
               {
                   clicked_2=true;
                   current_location=k;
                   break;
                }
           }
           if(clicked_2)
           {
               //指定对象
               switch(game->emit_locked)
               {
               case 1:game->card_battle_visiable_2[current_location].blood=1;
                   game->emit_locked=0;
                   break;
                   //肯定没野兽
               case 3:if(game->card_battle_visiable_2[current_location].zhongzu==pirate)
                   {
                       game->card_battle_visiable_2.erase(game->card_battle_visiable_2.begin()+current_location);
                       game->card_battle_visiable_1[game->emit_locked_help].attack++;
                       game->card_battle_visiable_1[game->emit_locked_help].blood++;
                       game->emit_locked=0;
                       game->emit_locked_help=-1;
                   }
                   break;

               case 5:if(game->card_battle_visiable_2[current_location].zhongzu==beast)
                   {
                       game->card_battle_visiable_2[current_location].attack=game->card_battle_visiable_2[current_location].attack+2;
                       game->card_battle_visiable_2[current_location].blood=game->card_battle_visiable_2[current_location].blood+2;
                       //嘲讽
                       game->emit_locked=0;
                   }
                   break;

               case 6:game->person_clear( game->card_battle_visiable_2[current_location]);
                   game->emit_locked=0;
                   break;
               }
           }

           update();
       }





       else if(game->emit_locked==0&&card_exist_clicked==0&&game->card_battle_visiable_2.size()!=0)
       {
           bool clicked_2=false;
           for(int k=0;k<game->card_battle_visiable_2.size();k++)
           {
               if(i>=920-65*game->card_battle_visiable_2.size()+130*k&&i<=920-65*game->card_battle_visiable_2.size()+130*k+100)
               {
                   clicked_2=true;
                   current_location=k;
                   break;
                }
           }
           //攻击
           if(game->current_side==1&&game->card_battle_visiable_2[current_location].attack_status==un_attacked)
           {
               attacker_x=i;
               attacker_y=j;
               game->attacker=current_location;
           }
       }

    }




    /*
     *
     * 下个回合
     */



    if(i>=1390&&i<=1540&&j>=425&&j<=480&&game->emit_locked==0&&card_exist_clicked==0&&game->attacker==-1)
    {
        game->current_side= (game->current_side+1)%2;
        game->round++;
        if(game->current_side==0)
        {
            game->energy_useable_1=game->round/2;
            if(game->energy_useable_1>=10)
                game->energy_useable_1=10;
            game->energy_1=game->energy_useable_1;
            if(game->cardpile_1.size()!=0)
            {
                game->card_hand_1.push_back(game->cardpile_1[0]);
                game->cardpile_1.erase(game->cardpile_1.begin());
            }
            for(int i=0;i<game->card_battle_visiable_1.size();i++)
                game->card_battle_visiable_1[i].attack_status=un_attacked;
            for(int i=0;i<game->card_battle_visiable_2.size();i++)
                game->card_battle_visiable_2[i].attack_status=attacked;
        }
        else
        {
            game->energy_useable_2=game->round/2;
            if(game->energy_useable_2>=10)
                game->energy_useable_2=10;
            game->energy_2=game->energy_useable_2;
            if(game->cardpile_2.size()!=0)
            {
                game->card_hand_2.push_back(game->cardpile_2[0]);
                game->cardpile_2.erase(game->cardpile_2.begin());
            }
            for(int i=0;i<game->card_battle_visiable_2.size();i++)
                game->card_battle_visiable_2[i].attack_status=un_attacked;
            for(int i=0;i<game->card_battle_visiable_1.size();i++)
                game->card_battle_visiable_1[i].attack_status=attacked;
        }
        update();
    }











    if(i>=830&&i<=970&&j>=160&&j<=260)
    {
        if(game->current_side==0&&game->hunter.weapeon!=0)
        {
            game->hero_attack=true;
            attacker_x=i;
            attacker_y=j;
        }
    }

    if(i>=830&&i<=970&&j>=720&&j<=845)    //战士
    {
        if(game->current_side==1&&game->warrior.weapeon!=0)
        {
            game->hero_attack=true;
            attacker_x=i;
            attacker_y=j;
        }
    }

    update();


    if(ui->stackedWidget->currentIndex()==0){







          }
          else if(ui->stackedWidget->currentIndex()==2){
              ui->stackedWidget->setCurrentIndex(3);
          }
         else if(ui->stackedWidget->currentIndex()==3){
              ui->stackedWidget->setCurrentIndex(4);
          }






}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    move_x=event->x();
    move_y=event->y();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter back(this);

    if(ui->stackedWidget->currentIndex()==0){

           back.drawPixmap(0,0,width(),height(),QPixmap("://`@X)UZ5IZ0B{IL{(IWY5L8E.png"));
       }
       else if(ui->stackedWidget->currentIndex()==1){
           //setUpdatesEnabled(1);
        playlist=new QMediaPlaylist;
        playlist->addMedia(QUrl::fromLocalFile("D:/music/炉石开始音乐.wav"));
         playlist->setPlaybackMode(QMediaPlaylist::Loop);
         movie->setPlaylist(playlist);
           movie->play();
             back.drawPixmap(0,0,width(),height(),QPixmap("://images/图层 12.png"));
       }
       else if(ui->stackedWidget->currentIndex()==2){
           back.drawPixmap(0,0,width(),height(),QPixmap("://图层 44.png"));
       }
       else if(ui->stackedWidget->currentIndex()==3){
             back.drawPixmap(0,0,width(),height(),QPixmap("://图层 43.png"));
       }


else{
        background_1.begin(this);
        b.load("://images/微信截图_20200920161131.png");
        background_1.drawPixmap(0,0,width(),height(),b);
        background_1.end();

        background_2.begin(this);
        b.load("://images/上层.png");
        background_2.drawPixmap(0,0,width(),height(),b);
        background_2.end();

        weilan.begin(this);
        b.load("://images/水晶槽.png");
       // weilan.drawPixmap(move_x,move_y,425,60,b);
        weilan.drawPixmap(1100,35,425,60,b);
        weilan.end();

        for(int i=0;i<game->energy_2;i++)
        {
            energy_two->begin(this);
            b.load("://images/法力水晶.png");
            energy_two->drawPixmap(1230+32*i,910,30,30,b);
            energy_two->end();
        }

        for(int i=0;i<game->energy_1;i++)
        {
            energy_one->begin(this);
            b.load("://images/法力水晶.png");
            energy_one->drawPixmap(1200+32*i,50,30,30,b);
            energy_one->end();
        }

        if(game->current_side==1)
        {
            end_round.begin(this);
            b.load("://images/结束回合.png");
            end_round.drawPixmap(1380,410,150,90,b);
            end_round.end();
        }

        if(game->hunter.weapeon!=0)
        {
            hunter_weapeon.begin(this);
            b.load("://images/图层 2.png");
            hunter_weapeon.drawPixmap(655,150,150,150,b);
            hunter_weapeon.end();

            if(game->hunter.useable_times_current<game->hunter.useable_times_base)
            {
                resistant.begin(this);
                b.load("://images/耐久/图层 23.png");
                resistant.drawPixmap(750,230,40,50,b);
                resistant.end();
            }
        }

        if(game->warrior.weapeon!=0)
        {
            warrior_weapeon.begin(this);
            if(game->warrior.weapeon==2)
                b.load("://images/重斧.png");
            else if(game->warrior.weapeon==3)
                b.load("://images/haidaogouzi.png");
            else if(game->warrior.weapeon==4)
                b.load("://images/chiyanzhanfu.png");
            else if(game->warrior.weapeon==5)
                b.load("://images/aojinfu.png");

            warrior_weapeon.drawPixmap(660,700,140,140,b);
            warrior_weapeon.end();

            if(game->warrior.useable_times_max==game->warrior.useable_times_current&&game->warrior.useable_times_max==game->warrior.useable_times_base)
            {

            }
            else if(game->warrior.useable_times_max==game->warrior.useable_times_current&&game->warrior.useable_times_max>game->warrior.useable_times_base)
            {
                resistant.begin(this);
                switch(game->warrior.useable_times_current)
                {
                case 3: b.load("://images/耐久/图层 19.png");break;
                case 4: b.load("://images/耐久/图层 20.png");break;
                case 5: b.load("://images/耐久/图层 24.png");break;
                }
                resistant.drawPixmap(750,780,40,50,b);
                resistant.end();

            }
            else
            {
                resistant.begin(this);
                switch(game->warrior.useable_times_current)
                {
                case 1:b.load("://images/耐久/图层 23.png");break;
                case 2:b.load("://images/耐久/图层 22.png");break;
                case 3:b.load("://images/耐久/图层 21.png");break;
                case 4:b.load("://images/耐久/图层 25.png");break;
                }
                resistant.drawPixmap(750,780,40,50,b);
                resistant.end();

            }



            if(game->warrior.attack_max>game->warrior.attack_base)
            {
                weapeon_max_attack.begin(this);
                switch (game->warrior.attack_max)
                {
                     case 2:b.load("://images/攻击/图层 6.png");break;
                     case 3:b.load("://images/攻击/图层 8.png");break;
                     case 4:b.load("://images/攻击/图层 11.png");break;
                     case 5:b.load("://images/攻击/绿色5.png");break;
                     case 6:b.load("://images/攻击/图层 13.png");break;
                     case 7:b.load("://images/攻击/图层 14.png");break;
                     case 8:b.load("://images/攻击/图层 16.png");break;
                }
                weapeon_max_attack.drawPixmap(650,775,35,55,b);
                weapeon_max_attack.end();
            }
        }



        for(int i=0;i<game->card_hand_1.size();i++)
        {

            a[i].begin(this);
            put_picure(b,game->card_hand_1[i].which);
            if(game->card_hand_1[i].clicked==false)
            a[i].drawPixmap(870-25*game->card_hand_1.size()+50*i,0,100,150,b);
            else
                a[i].drawPixmap(move_x,move_y,100,150,b);
            a[i].end();
        }
        for(int i=0;i<game->card_hand_2.size();i++)
        {

            d[i].begin(this);
            put_picure(b,game->card_hand_2[i].which);
            if(game->card_hand_2[i].clicked==false)
            d[i].drawPixmap(870-25*game->card_hand_2.size()+50*i,850,100,150,b);
            else
                d[i].drawPixmap(move_x,move_y,100,150,b);
            d[i].end();
        }




        for(int i=0;i<game->card_battle_visiable_1.size();i++)
        {
            c[i].begin(this);
            put_picure_(b,game->card_battle_visiable_1[i].which);
            if(begin_number==i&&game->current_side==0)
                c[i].drawPixmap(920-65*game->card_battle_visiable_1.size()+130 *i+(-65*game->card_battle_visiable_2.size()+130 *end_number+65*game->card_battle_visiable_1.size()-130*i)/10*timecount,
                                    300+20*timecount,100,150,b);
            else if (attack_hero==2&&i==attack_hero_from)
                c[i].drawPixmap(920-65*game->card_battle_visiable_1.size()+130 *i+(920-920+65*game->card_battle_visiable_1.size()-130 *i)/35*timecount,
                                300+20*timecount,100,150,b);
            else
            c[i].drawPixmap(920-65*game->card_battle_visiable_1.size()+130 *i,300,100,150,b);
            c[i].end();




            if((begin&&begin_number==i)||attack_hero!=0)
            {
            }
            else
            {
                if(game->card_battle_visiable_1[i].attack_status==un_attacked)
                {
                    green.begin(this);
                    if(game->card_battle_visiable_1[i].shield==0)
                    b.load("://images/图层 48.png");
                    else {
                        b.load("://images/shield_attack.png");
                    }
                    green.drawPixmap(920-65*game->card_battle_visiable_1.size()+130 *i,300,100,150,b);
                    green.end();
                }
                else {
                    if(game->card_battle_visiable_1[i].shield)
                    {
                        shield.begin(this);
                        b.load("://images/shield_all.png");
                        shield.drawPixmap(920-65*game->card_battle_visiable_1.size()+130 *i,300,100,150,b);
                        shield.end();
                    }
                }
            }

                blood_1[i].begin(this);
                judge_blood(b,game->card_battle_visiable_1[i].blood);
                if(begin_number==i&&game->current_side==0)
                    blood_1[i].drawPixmap(920-65*game->card_battle_visiable_1.size()+130 *i+(-65*game->card_battle_visiable_2.size()+130 *end_number+65*game->card_battle_visiable_1.size()-130*i)/10*timecount+64,
                                          390+20*timecount,23,40,b);
                else if (attack_hero==2&&i==attack_hero_from)
                    blood_1[i].drawPixmap(920-65*game->card_battle_visiable_1.size()+130 *i+(920-920+65*game->card_battle_visiable_1.size()-130 *i)/35*timecount+64,
                                          390+20*timecount,23,40,b);
                else
                blood_1[i].drawPixmap(920-65*game->card_battle_visiable_1.size()+130 *i+64,390,23,40,b);
                blood_1[i].end();


                attack_1[i].begin(this);
                judge_attack(b,game->card_battle_visiable_1[i].attack);
                if(begin_number==i&&game->current_side==0)
                    attack_1[i].drawPixmap(920-65*game->card_battle_visiable_1.size()+130 *i+(-65*game->card_battle_visiable_2.size()+130 *end_number+65*game->card_battle_visiable_1.size()-130*i)/10*timecount+10,
                                           386+20*timecount,28,43,b);
                else if (attack_hero==2&&i==attack_hero_from)
                    attack_1[i].drawPixmap(920-65*game->card_battle_visiable_1.size()+130 *i+(920-920+65*game->card_battle_visiable_1.size()-130 *i)/35*timecount+10,
                                          386+20*timecount,28,43,b);
                else
                attack_1[i].drawPixmap(920-65*game->card_battle_visiable_1.size()+130 *i+10,386,28,43,b);
                attack_1[i].end();

                if(timecount>14&&attack_hero==2)
                {
                    deal_attack_warrior();
                    attack_hero_from=-1;
                    attack_hero=0;
                }



                if(timecount>4&&begin)
            {
                game->deal_attack(game->current_side,begin_number,end_number);
                begin_number=-1;
                end_number=-1;
                //timecount=0;
                begin=false;
            }
        }

        for(int i=0;i<game->card_battle_visiable_2.size();i++)
        {
            if(game->card_battle_visiable_2[i].legend==false)
            {
                f[i].begin(this);
                put_picure_(b,game->card_battle_visiable_2[i].which);
                if(begin_number==i&&game->current_side==1)
                    f[i].drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i+(-65*game->card_battle_visiable_1.size()+130 *end_number+65*game->card_battle_visiable_2.size()-130*i)/10*timecount,
                                    500-20*timecount,100,150,b);
                else if (attack_hero==1&&i==attack_hero_from)
                    f[i].drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i+(920-920+65*game->card_battle_visiable_2.size()-130 *i)/35*timecount,
                                    500-20*timecount,100,150,b);
                else
                f[i].drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i,500,100,150,b);
                f[i].end();
            }
            else {
                f[i].begin(this);
                put_picure_(b,game->card_battle_visiable_2[i].which);
                if(begin_number==i&&game->current_side==1)
                    f[i].drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i+(-65*game->card_battle_visiable_1.size()+130 *end_number+65*game->card_battle_visiable_2.size()-130*i)/10*timecount,
                                    500-20*timecount,120,150,b);
                else if (attack_hero==1&&i==attack_hero_from)
                    f[i].drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i+(920-920+65*game->card_battle_visiable_2.size()-130 *i)/35*timecount,
                                    500-20*timecount,120,150,b);
                else
                f[i].drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i,500,100,150,b);
                f[i].end();
            }


            if((begin&&begin_number==i)||attack_hero==1)
            {

            }
            else
            {
                if(game->card_battle_visiable_2[i].attack_status==un_attacked)
                {
                    green.begin(this);
                    if(game->card_battle_visiable_2[i].shield==0)
                    b.load("://images/图层 48.png");

                    else {
                        b.load("://images/shield_attack.png");
                    }
                    green.drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i,500,100,150,b);
                    green.end();
                }
                else {
                    if(game->card_battle_visiable_2[i].shield)
                    {
                        shield.begin(this);
                        b.load("://images/shield_all.png");
                        shield.drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i,500,100,150,b);
                        shield.end();
                    }
                }
            }


            blood_2[i].begin(this);
            judge_blood(b,game->card_battle_visiable_2[i].blood);
            if(begin_number==i&&game->current_side==1)
                blood_2[i].drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i+(-65*game->card_battle_visiable_1.size()+130 *end_number+65*game->card_battle_visiable_2.size()-130*i)/10*timecount+70,
                                      590-20*timecount,23,40,b);
            else if (attack_hero==1&&i==attack_hero_from)
                blood_2[i].drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i+(920-920+65*game->card_battle_visiable_2.size()-130 *i)/35*timecount+70,
                                590-20*timecount,23,40,b);
            else
                blood_2[i].drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i+70,590,23,40,b);
            blood_2[i].end();

            attack_2[i].begin(this);
            judge_attack(b,game->card_battle_visiable_2[i].attack);
            if(begin_number==i&&game->current_side==1)
                attack_2[i].drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i+(-65*game->card_battle_visiable_1.size()+130 *end_number+65*game->card_battle_visiable_2.size()-130*i)/10*timecount+5,
                                      586-20*timecount,28,43,b);
            else if (attack_hero==1&&i==attack_hero_from)
                attack_2[i].drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i+(920-920+65*game->card_battle_visiable_2.size()-130 *i)/35*timecount+5,
                                586-20*timecount,28,43,b);
            else
            attack_2[i].drawPixmap(920-65*game->card_battle_visiable_2.size()+130 *i+5,586,28,43,b);
            attack_2[i].end();

            if(timecount>4&&begin)
            {
                game->deal_attack(game->current_side,begin_number,end_number);
                begin_number=-1;
                end_number=-1;
                //timecount=0;
                begin=false;
            }

            if(timecount>14&&attack_hero==1)
            {
                deal_attack_hunter();
                attack_hero_from=-1;
                attack_hero=0;
            }
        }

        hunter_blood.begin(this);
        put_picure_hero(b,game->hunter.blood);
        hunter_blood.drawPixmap(945,200,50,70,b);
        hunter_blood.end();

        warrior_blood.begin(this);
        put_picure_hero(b,game->warrior.blood);
        warrior_blood.drawPixmap(945,785,50,70,b);
        warrior_blood.end();







        //attacker_x=500;attacker_y=500;
        if(attacker_x!=-1&&attacker_y!=-1)
        {
            jiantou.begin(this);
            if(move_x>=attacker_x+40&&move_y>=attacker_y+40)
            {
                b.load("://images/图层 2 - 副本 - 副本 (2).png");
                jiantou.drawPixmap(attacker_x,attacker_y,move_x-attacker_x,move_y-attacker_y,b);
            }
            else if(move_x>=attacker_x+40&&move_y+40<=attacker_y)
            {
                b.load("://images/jiantou.png");
                jiantou.drawPixmap(attacker_x,move_y,move_x-attacker_x,attacker_y-move_y,b);
            }
            else if(move_x<=attacker_x-40&&move_y<=attacker_y-40)
            {
                b.load("://images/图层 2 - 副本 - 副本.png");
                jiantou.drawPixmap(move_x,move_y,attacker_x-move_x,attacker_y-move_y,b);
            }
            else if(move_x<=attacker_x-40&&move_y-40>=attacker_y)
            {
                b.load("://images/图层 2 - 副本.png");
                jiantou.drawPixmap(move_x,attacker_y,attacker_x-move_x,move_y-attacker_y,b);
            }
            else if(move_x<=attacker_x+40&&move_x>=attacker_x-40&&move_y<=attacker_y)
            {
                b.load("://images/2.png");
                jiantou.drawPixmap(attacker_x-40,move_y,80,attacker_y-move_y,b);
            }

            else if(move_x<=attacker_x+40&&move_x>=attacker_x-40&&move_y>=attacker_y)
            {
                b.load("://images/4.png");
                jiantou.drawPixmap(attacker_x-40,attacker_y,80,move_y-attacker_y,b);
            }

            else if(move_y<=attacker_y+40&&move_y>=attacker_y-40&&move_x>=attacker_x)
            {
                b.load("://images/1.png");
                jiantou.drawPixmap(attacker_x,attacker_y-40,move_x-attacker_x,80,b);
            }

            else if(move_y<=attacker_y+40&&move_y>=attacker_y-40&&move_x<=attacker_x)
            {
                b.load("://images/3.png");
                jiantou.drawPixmap(move_x,attacker_y-40,attacker_x-move_x,80,b);
            }
            jiantou.end();

        }


}




}


void MainWindow::put_picure(QPixmap &b, int c)
{

    if(c==0)
        b.load("://images/猎人印记.png");
    else if(c==1)
        b.load("://images/追踪术.png");
    else if(c==2)
        b.load("://images/card10.png");
    else if(c==3)
        b.load("://images/card2.png");
    else if(c==4)
        b.load("://images/card4.png");
    else if(c==5)
        b.load("://images/card3.png");
    else if(c==6)
        b.load("://images/card11.png");
    else if(c==7)
        b.load("://images/card12.png");
    else if(c==8)
        b.load("://images/card13.png");
    else if(c==9)
        b.load("://images/海盗蟹.png");
    else if(c==10)
        b.load("://images/card14.png");
    else if(c==11)
        b.load("://images/card15.png");
    else if(c==12)
        b.load("://images/card5.png");
    else if(c==13)
        b.load("://images/card6.png");
    else if(c==14)
        b.load("://images/card17.png");
    else if(c==15)
        b.load("://images/card16.png");
    else if(c==16)
        b.load("://images/card7.png");
    else if(c==18)
        b.load("://images/card8.png");
    else if(c==19)
        b.load("://images/card9.png");




    else if(c==30)
        b.load("://images/图层 16.png");
    else if(c==31)
        b.load("://images/图层 15.png");
    else if(c==32)
        b.load("://images/图层 17.png");
    else if(c==33)
        b.load("://images/图层 18.png");
    else if(c==34)
        b.load("://images/xuefan.png");
    else if(c==35)
        b.load("://images/图层 19.png");
    else if(c==36)
        b.load("://images/图层 21.png");
    else if(c==37)
        b.load("://images/图层 20.png");
    else if(c==38)
        b.load("://images/图层 22.png");
    else if(c==39)
        b.load("://images/图层 24.png");
    else if(c==40)
        b.load("://images/图层 25.png");
    else if(c==41)
        b.load("://images/图层 27.png");
    else if(c==42)
        b.load("://images/图层 23.png");
    else if(c==43)
        b.load("://images/图层 26.png");
    else if(c==44)
        b.load("://images/图层 28.png");
    else if(c==45)
        b.load("://images/图层 29.png");
    else if(c==46)
        b.load("://images/aojing fu.png");

}

void MainWindow::put_picure_(QPixmap &b, int c)
{
    if(c==2)
        b.load("://images/female.png");
    else if(c==3)
        b.load("://images/森林狼随从.png");
    else if(c==4)
        b.load("://images/吃武器.png");
    else if(c==5)
        b.load("://images/先锋.png");
    else if(c==6)
        b.load("://images/土狼.png");
    else if(c==7)
        b.load("://images/图层 4.png");
    else if(c==8)
        b.load("://images/雷鸣.png");
    else if(c==9)
        b.load("://images/海盗蟹 随从.png");
    else if(c==15)
        b.load("://images/进化龙.png");
    else if(c==16)
        b.load("://images/加二加二.png");
    else if(c==18)
        b.load("://images/犀牛.png");
    else if(c==19)
        b.load("://images/狮子.png");



    else if(c==30)
        b.load("://images/图层 36.png");
    else if(c==32)
        b.load("://images/图层 38.png");
    else if(c==33)
        b.load("://images/图层 31.png");
    else if(c==34)
        b.load("://images/图层 30.png");
    else if(c==35)
        b.load("://images/图层 33.png");
    else if(c==37)
        b.load("://images/图层 32.png");
    else if(c==38)
        b.load("://images/图层 35.png");
    else if(c==39)
        b.load("://images/terr_without_shield.png");
    else if(c==40)
        b.load("://images/图层37.png");
    else if(c==42)
        b.load("://images/图层 40.png");
    else if(c==43)
        b.load("://images/图层 39.png");
    else if(c==44)
        b.load("://images/图层 42.png");
    else if(c==45)
        b.load("://images/captain_场上.png");
    else if(c==50)
        b.load("://images/male.png");
    else if(c==51)
        b.load("://images/狼.png");
    else if(c==52)
        b.load("://images/狗.png");
    else if(c==53)
        b.load("://images/chongfengzhu.png");
    else if(c==54)
        b.load("://images/雷欧克.png");
    else if(c==55)
        b.load("://images/黑熊.png");
    else if(c==58)
        b.load("://images/图层 41.png");
    else if(c==59)
        b.load("://images/狮子。。。.png");
}

void MainWindow::judge_blood(QPixmap &b, int c)
{
    if(c==1)
        b.load("://images/b1.png");
    else if(c==2)
        b.load("://images/b2.png");
    else if(c==3)
        b.load("://images/b3.png");
    else if(c==4)
        b.load("://images/b4.png");
    else if(c==5)
        b.load("://images/b5.png");
    else if(c==6)
        b.load("://images/b6.png");
    else if(c==7)
        b.load("://images/b7.png");
    else if(c==8)
        b.load("://images/b8.png");
    else if(c==9)
        b.load("://images/b9.png");
    else if(c==10)
        b.load("://images/b10.png");
    else if(c==11)
        b.load("://images/b11.png");
    else if(c==12)
        b.load("://images/b12.png");
}

void MainWindow::judge_attack(QPixmap &b, int c)
{
    if(c==1)
        b.load("://images/a1.png");
    else if(c==2)
        b.load("://images/a2.png");
    else if(c==3)
        b.load("://images/a3.png");
    else if(c==4)
        b.load("://images/a4.png");
    else if(c==5)
        b.load("://images/a5.png");
    else if(c==6)
        b.load("://images/a6.png");
    else if(c==7)
        b.load("://images/a7.png");
    else if(c==8)
        b.load("://images/a8.png");
    else if(c==9)
        b.load("://images/a9.png");
    else if(c==10)
        b.load("://images/a10.png");

}


void MainWindow::put_picure_hero(QPixmap &b, int c)
{
    if(c==1)
        b.load("://images/person_blood/图层 42.png");
    else if(c==2)
        b.load("://images/person_blood/图层 41.png");
    else if(c==3)
        b.load("://images/person_blood/图层 40.png");
    else if(c==4)
        b.load("://images/person_blood/图层 39.png");
    else if(c==5)
        b.load("://images/person_blood/图层 38.png");
    else if(c==6)
        b.load("://images/person_blood/图层 37.png");
    else if(c==7)
        b.load("://images/person_blood/图层 36.png");
    else if(c==8)
        b.load("://images/person_blood/图层 35.png");
    else if(c==9)
        b.load("://images/person_blood/图层 34.png");
    else if(c==10)
        b.load("://images/person_blood/图层 33.png");
    else if(c==11)
        b.load("://images/person_blood/图层 61.png");
    else if(c==12)
        b.load("://images/person_blood/图层 19.png");
    else if(c==13)
        b.load("://images/person_blood/图层 18.png");
    else if(c==14)
        b.load("://images/person_blood/图层 17.png");
    else if(c==15)
        b.load("://images/person_blood/图层 16.png");
    else if(c==16)
        b.load("://images/person_blood/图层 15.png");
    else if(c==17)
        b.load("://images/person_blood/图层 14.png");
    else if(c==18)
        b.load("://images/person_blood/图层 60.png");
    else if(c==19)
        b.load("://images/person_blood/图层 59.png");
    else if(c==20)
        b.load("://images/person_blood/图层 58.png");
    else if(c==21)
        b.load("://images/person_blood/图层 57.png");
    else if(c==22)
        b.load("://images/person_blood/图层 56.png");
    else if(c==23)
        b.load("://images/person_blood/图层 55.png");
    else if(c==24)
        b.load("://images/person_blood/图层 54.png");
    else if(c==25)
        b.load("://images/person_blood/图层 53.png");
    else if(c==26)
        b.load("://images/person_blood/图层 52.png");
    else if(c==27)
        b.load("://images/person_blood/图层 51.png");
    else if(c==28)
        b.load("://images/person_blood/图层 50.png");
    else if(c==29)
        b.load("://images/person_blood/图层 49.png");
    else if(c==30)
        b.load("://images/person_blood/30.png");
}



void MainWindow::deal_attack_hunter()
{
    if(game->current_side==1&&game->attacker!=-1)
            {
        attack_hero=0;

                game->hunter.blood-=game->card_battle_visiable_2[game->attacker].attack;
                game->card_battle_visiable_2[game->attacker].attack_status=attacked;
                game->attacker=-1;
            }
    if(game->hunter.blood<1)
    {
        //赢
        victory=new QMainWindow;
                              victory->setStyleSheet("border-image:url(://微信截图_20200916161401.png)");
                              victory->show();
                              victory->setWindowState(Qt::WindowMaximized);
    }
    update();
}

void MainWindow::deal_attack_warrior()
{
    if(game->current_side==0&&game->attacker!=-1)
            {attack_hero=0;

                game->warrior.blood-=game->card_battle_visiable_1[game->attacker].attack;
                game->card_battle_visiable_1[game->attacker].attack_status=attacked;
                game->attacker=-1;
            }
    if(game->warrior.blood<1)
    {
        //输
        lose=new QMainWindow;
        lose->setStyleSheet("border-image:url(://微信截图_20200916160830.png)");
        lose->show();
        lose->setWindowState(Qt::WindowMaximized);

    }
    update();
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}
