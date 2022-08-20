#ifndef ACTIONRANDOM_H
#define ACTIONRANDOM_H

#include <QMainWindow>
#include <QMenuBar>
#include "mycoin.h"

class Actionrandom : public QMainWindow
{
    Q_OBJECT
public:
    explicit Actionrandom(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    int gameAry[4][4];//二维数组维护每一关的具体数据

    MyCoin * btnCoin[4][4];
    //是否胜利
    bool isWin;



signals:

};

#endif // ACTIONRANDOM_H
