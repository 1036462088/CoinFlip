#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QDialog>
#include <QMessageBox>
#include <QSound> //多媒体模块下的音效头文件


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //配置主场景
    //设置固定大小
    setFixedSize(420,620);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币");

    //退出按钮的实现                   触发
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //随机按钮实现
    connect(ui->actionrandom,&QAction::triggered,[=](){
        QMessageBox *mb=new QMessageBox(this);
        //dlg.setWindowTitle("Hello");
     QMessageBox::StandardButton stb=  mb->information(this,"随机模式",
                                                       "您确定进入随机模式吗？(进入该模式后每次点击将在点击的位置和周围（上下左右随机一个位置）翻转硬币)"
                                        ,QMessageBox::Yes|QMessageBox::No);
     if(stb==QMessageBox::Yes)
     {
         actionrandom =new Actionrandom(this);
         this->hide();
         actionrandom->show();
     }

    });


    //游戏简介按钮实现
    connect(ui->actionjian_jie,&QAction::triggered,[=](){
        //QDialog dlg(this);
        QMessageBox *mb=new QMessageBox(this);
        //dlg.setWindowTitle("Hello");
     QMessageBox::StandardButton stb=  mb->information(this,"游戏简介","翻金币，"
                        "一款关于金币的休闲趣味益智游戏，简单的规则，"
                       "只需要把所有金币翻到正面，消除银币，即可过关，关卡形式丰富，花样多多，"
                       "后面的关卡超级难，仔细思考，才能过关"
                       "来挑战你的IQ吧,"
                       "天天翻金币，生活多有趣"
                       ",天天消除银币，体验胜利果实。"
                       "are you ready?",QMessageBox::Yes|QMessageBox::No);
     if(stb==QMessageBox::No)
     {
         this->close();
     }

        //dlg.resize(600,400);

        //dlg.exec();

    });

    //准备开始按钮的音效
    QSound *startSound =new QSound(":/res/TapButtonSound.wav",this);
    QSound *sound=new QSound(":/res/02.wav",this);
    sound->setLoops(-1);

    sound->play();


    //开始按钮实现
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.65-startBtn->width(),this->height()*0.7);
    //实例化选择关卡的场景
    chooseScene=new chooseLevelScene(this);//将父类的指针传给基类 方便之后使用parentWidget函数返回主界面



    connect(startBtn,&QPushButton::clicked,[=](){
        //播放开始音效资源
        startSound->play();
        //sound->stop();


        //做弹起特效
        startBtn->zoom1();
        startBtn->zoom2();
        //延时进入到选择关卡场景
        QTimer::singleShot(300,this,[=](){


            //进入选择关卡的场景中
            //自身隐藏
            this->hide();
            //显示选择关卡的界面  设值chooseScene场景位置
            chooseScene->setGeometry(this->geometry());

            chooseScene->show();

        });



    });

}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/3c05d82a965446f4.jpg");
    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画背景上的图标
    pix.load(":/res/Title.png");
    pix= pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

