#include "actionrandom.h"
#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QPalette>
#include "mycoin.h"
#include "config.h"
#include <QPropertyAnimation>
#include <QSound>





Actionrandom::Actionrandom(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(420,620);
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("随机模式");

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
    QSound* flipSound=new QSound(":/res/ConFlipSound.wav",this);
    QSound* winSound=new QSound(":/res/LevelWinSound.wav",this);

    //胜利图片的显示
  QLabel* winLabel=new QLabel(this);
  QPixmap tmpPix;
  tmpPix.load(":/res/LevelCompletedDialogBg.png");
  winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
  winLabel->setPixmap(tmpPix);
  winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());

  //设置字体
  QLabel *label=new QLabel(this);
  QFont font;
  font.setFamily("华文新魏");
  //设置字号
  font.setPointSize(20);
  //设置字体颜色
  QPalette pe;
  pe.setColor(QPalette::WindowText,Qt::darkBlue);
  label->setPalette(pe);
  label->setText("随机模式");
  //将字体设置到标签控件中
  label->setFont(font);
  //设置位置和大小
  label->setGeometry(10,this->height()-600,120,60);

    //显示金币背景图案
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QPixmap pix=QPixmap(":/res/BoardNode(1).png");
            QLabel*label=new QLabel(this);
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->move(120+i*50,210+j*50);


            //创建金币
            QString str;
            if(this->gameAry[i][j]==1)
            {
                //显示金币
                str=":/res/Coin0001.png";
            }
            else
            {
                //显示银币
                str=":/res/Coin0008.png";
            }
            MyCoin* coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(123+i*50,212+j*50);
            //给金币属性赋值
            coin->x=i;
            coin->y=j;
            coin->flag= this->gameAry[i][j];//1正面  0反面

            //将金币放入 到金币的二维数组里 便于后期维护
            btnCoin[i][j]=coin;


            //点击金币进行反转
            connect(coin,&MyCoin::clicked,[=](){
                flipSound->play();
                //在点击的时候禁用按钮
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        btnCoin[i][j]->isWin = true;

                    }
                }


                coin->changeFlag();
                this->gameAry[i][j]=this->gameAry[i][j] == 0 ? 1 : 0;
                //翻转周围的金币 延时反转

                QTimer::singleShot(300,[=](){
                    int i = rand()%3;
                    if(i==0)
                    {
                        if(coin->x+1<=3)//右侧金币反转
                        {
                            btnCoin[coin->x+1][coin->y]->changeFlag();
                            this->gameAry[coin->x+1][coin->y]=this->gameAry[coin->x+1][coin->y] == 0 ? 1 : 0;

                        }
                    }
                    if(i==1)
                    {
                        if(coin->x-1>=0)//左
                        {
                            btnCoin[coin->x-1][coin->y]->changeFlag();
                            this->gameAry[coin->x-1][coin->y]=this->gameAry[coin->x-1][coin->y] == 0 ? 1 : 0;
                        }
                    }
                    if(i==2)
                    {
                        if(coin->y+1<=3)//下
                        {
                            btnCoin[coin->x][coin->y+1]->changeFlag();
                            this->gameAry[coin->x][coin->y+1]=this->gameAry[coin->x][coin->y+1] == 0 ? 1 : 0;
                        }
                    }
                    if(i==3)
                    {
                        if(coin->y-1>=0)//上
                        {
                            btnCoin[coin->x][coin->y-1]->changeFlag();
                            this->gameAry[coin->x][coin->y-1]=this->gameAry[coin->x][coin->y-1] == 0 ? 1 : 0;
                        }
                    }



                    for(int i=0;i<4;i++)
                    {
                        //周围按钮全部翻完解除禁用
                        for(int j=0;j<4;j++)
                        {
                            btnCoin[i][j]->isWin = false;

                        }
                     }

                    //判断是否胜利
                    this->isWin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++){
                            if(btnCoin[i][j]->flag==false){
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin==true)
                    {
                        //qDebug()<<"胜利";
                        //将所有按钮的胜利标志改为true
                        winSound->play();

                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                btnCoin[i][j]->isWin = true;

                            }

                        }

                        //胜利
                        QPropertyAnimation * animation=new QPropertyAnimation(winLabel,"geometry");

                        //设置时间间隔
                        animation->setDuration(1000);
                        //开始
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),
                                                       winLabel->width(),winLabel->height()));


                        //结束
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,
                                                     winLabel->width(),winLabel->height()));


                        //曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);

                        //执行动画
                        animation->start();

                    }

                });
            });
        }
    }


}





void Actionrandom::paintEvent(QPaintEvent *)
{
    //设置背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/3c81c3326c6c5bac.jpg");
    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    //加载背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
//    pix.load(":/res/Title.png");
//    painter.drawPixmap(this->width()-pix.width()-65,30,pix.width(),pix.height(),pix);
}
