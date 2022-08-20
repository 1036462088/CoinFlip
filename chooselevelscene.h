#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class chooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseLevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
    PlayScene *play=NULL;


signals:

};

#endif // CHOOSELEVELSCENE_H
