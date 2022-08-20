#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);

    //参数代表传入的时金币的路径还是银币的路径
     MyCoin(QString btnImg);
     //金币的属性
     int x;
     int y;
     bool flag;

     //加载图片
     void Loadpicture(QPixmap pix);


     //改变标志的方法
    void changeFlag();

    QTimer *timer1 = new QTimer(this);//正面翻反面
    QTimer *timer2 = new QTimer(this);//反面反正面

    int min=1;
    int max=8;

    //执行动画的标志
    bool isAnimation=false;

    //重写 按下
    void mousePressEvent(QMouseEvent *e);

    //是否胜利
    bool isWin=false;


signals:

};

#endif // MYCOIN_H
