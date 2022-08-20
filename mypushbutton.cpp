#include "mypushbutton.h"
#include <QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}
void MyPushButton::iconShow(QString path)
{
    QPixmap pix;
    bool ret=pix.load(path);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(),pix.height());//设置图片固定大小
    this->setStyleSheet("QPushButton{border:0px;}");//设置不规则图片样式
    this->setIcon(pix);//设置图标
    this->setIconSize(QSize(pix.width(),pix.height()));//设置图标大小
}

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    iconShow(normalImg);
}

void MyPushButton::zoom(int path_1,int path_2)
{
    //创建动态对象
    QPropertyAnimation  *animation=new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+path_2,this->width(),this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+path_1,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}
//向下跳
void MyPushButton::zoom1()
{
    zoom(10,0);

}
//向上跳
void MyPushButton::zoom2()
{

    zoom(0,10);
}

//重写按钮的按下和释放事件
void MyPushButton::mousePressEvent(QMouseEvent*e)
{

    if(this->pressImgPath!="")//传入的按下图片不为空 说明需要按下后切换图片
    {
        iconShow(this->pressImgPath);
    }

    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent*e)
{

    if(this->pressImgPath!="")//传入的按下图片不为空 说明需要按下后切换成初始图片
    {
        iconShow(this->normalImgPath);
    }

    //让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}


