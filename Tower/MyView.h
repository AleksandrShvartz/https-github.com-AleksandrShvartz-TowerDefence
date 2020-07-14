#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include "MyButton.h"
#include "Header.h"
#include "Castle.h"
#include "CrossBow.h"
#include "Arrow.h"
#include "ValuesOfGame.h"
#include "Enomy.h"
class MyView :
    public QGraphicsView
{
    Q_OBJECT
public:
    MyView();
    void startGame();
    void pauseGame();
    void endOfTheGame();
    void mouseMoveEvent(QMouseEvent*) override;
   void keyPressEvent(QKeyEvent*) override;
   ~MyView();
signals:
   // void sendTorefreshValues();
   void mouseMoved(qreal, bool);
private:
    void initElements();
    void reload();
private slots:
    void btnPlayClicked(Qt::MouseButton);
    void btnPauseClicked(Qt::MouseButton);
    void refreshTime();
    void createEnomy();
private:
    ValuesOfGame* val;
    QGraphicsScene scene;
    Castle tower;
    CrossBow bow;
    MyButton btnPause;
    MyButton btnPlay;
    QVector<Arrow*> arrows;
    bool gameStarted;
    bool onPause;
    QMediaPlayer* mediaOfShot,*mediaOfScream,*mediaOfHit,*mediaOfEnd,*mediaOfDeath,*mediaOfCreate;
//    int arrowX;
 //   int arrowY;
 //   qreal arrowAngle;
    bool estSnariad;
    qreal bowAngle;
    int bowX;
    int bowY;
    QTimer timer,timer2,timer3;
  //  Enomy vragi[10];
    QVector<Enomy*>vragi;
  //  int countOfEnomy;
};

