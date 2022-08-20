#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum,QWidget *parent = nullptr);
    int levelIndex;//内部成员属性记录所选关卡

    void paintEvent(QPaintEvent *);


    int gameAry[4][4];//二维数组维护每一关的具体数据

    MyCoin * btnCoin[4][4];
    //是否胜利
    bool isWin;




signals:

};

#endif // PLAYSCENE_H
