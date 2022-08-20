#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QSound>
#include "mainwindow.h"

chooseLevelScene::chooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(420,620);
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar *bar= menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu= bar->addMenu("开始");
    //创建返回的菜单项
    QAction *backAction = startMenu->addAction("返回");
    //创建退出的菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //点击返回 实现返回
    connect(backAction,&QAction::triggered,[=](){
        QTimer::singleShot(200,this,[=](){

            this->hide();


            //通过parentWidget返回上一级菜单 需要返回几级菜单就调用几次parentWidget 使用时需确保上一级界面指针传递到本界面
            this->parentWidget()->show();


        });


    });
    //点击退出 实现退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });


    QSound* chooseSound=new QSound(":/res/TapButtonSound.wav",this);


    QSound* backSound=new QSound(":/res/BackButtonSound.wav",this);
    //QSound* sound=new QSound(":/res/01SplashGreen.wav",this);


    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&MyPushButton::clicked,[=](){
        //sound->stop();

        backSound->play();



        QTimer::singleShot(300,this,[=](){

            this->hide();

            this->parentWidget()->show();
        });

    });

   //创建选择关卡的按钮
    for(int i=0;i<20;i++)
    {
        //一个for循环写出矩阵
        MyPushButton* menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        //起始值+每行个数*间距      起始值+每列个数*间距
        menuBtn->move(80 + i%4*70,200 + i/4*70);

        //监听每个按钮的点击事件
        connect(menuBtn,&QPushButton::clicked,[=](){

            chooseSound->play();
            //进入到游戏场景
              play=new PlayScene(i+1,this);
              this->hide();
              play->show();

        });

        QLabel *label=new QLabel(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(80 + i%4*70,200 + i/4*70);
        //设置label对齐方式      水平居中  和  垂直居中
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置让鼠标进行穿透   51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }
}

void chooseLevelScene::paintEvent(QPaintEvent *)
{
    //设置背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/-28d0db23eb6c7141.jpg");
    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap(this->width()-pix.width()-65,30,pix.width(),pix.height(),pix);

}
