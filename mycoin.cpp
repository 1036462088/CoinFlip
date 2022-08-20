#include "mycoin.h"
#include <QDebug>
#include <QPixmap>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret= pix.load(btnImg);
    if(!ret)
    {
        QString str=QString("图片 %1 加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }
    Loadpicture(pix);


    //监听金币反转的信号
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        Loadpicture(pix);
        //判断 如果翻完了 将min重置为1
        if(this->min>this->max)
        {
            this->min=1;
            isAnimation=false;
            timer1->stop();
        }
    });
    //监听银币反转的信号
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        Loadpicture(pix);
        //判断 如果翻完了 将min重置为1
        if(this->max<this->min)
        {
            this->max=8;
            isAnimation=false;
            timer2->stop();
        }
    });
}
//加载图片
void MyCoin::Loadpicture(QPixmap pix)
{

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation||this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}

//改变正反面标志的方法
void MyCoin::changeFlag()
{
    //如果是正面 翻成反面
    if(this->flag)
    {
        //开启正面翻反面的定时器
        timer1->start(30);
        isAnimation=true;//开始执行动画
        this->flag=false;
    }
    else
    {
        timer2->start(30);
        isAnimation=true;
        this->flag=true;
    }
}
