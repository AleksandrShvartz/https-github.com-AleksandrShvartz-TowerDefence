#pragma once
#include "Header.h"
class Enomy :
    public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    //задаем область для перерисовки
    QRectF boundingRect() const override;
    //рисуем
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QPointF getCoords();
    void setCoords(QPointF);
    void setAng(qreal ang);
    qreal getAngl();
    void setHealth(int);
    int getHealth();
private:
    int coordX=0;
    int coordY = 0;
    int w= heigthOfEnomy;
    int h= widthOfEnomy;
    QString path=0;
    int damage=damageOfEnomy;
    int health=healthOfEnomy;
    int speed=speedOfEnomy;
    int angleOfEnomy;
};

