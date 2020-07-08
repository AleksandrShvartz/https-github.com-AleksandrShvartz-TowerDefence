#pragma once
#include "Header.h"
class Arrow :
    public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
     Arrow(QString, int a, int b, int dam,int x,int y,qreal angl);
     void setFly(bool b);
     bool getFly();
     void setCoords(QPointF);
     void setAngle(qreal);
     void setConstAngle(qreal);
     qreal getAngle();
     qreal getConstAngle();
     QPointF getCoords();
     Arrow();
    //задаем область для перерисовки
    QRectF boundingRect() const override;
    //рисуем
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
  //  void keyPressEvent(QKeyEvent* )override;
public slots:
    //void refreshCoords();
    void mmoveMouse(qreal an,bool);
   // void timeIsOut();
private:
    int damage = 0;
    int w = 0;
    int h = 0;
    int coordX = 0;
    int coordY = 0;
    QString path = 0;
    qreal constAngle = 0;
    qreal angle = 0;
    bool inFly = false;
  //  QTimer timer;
};

