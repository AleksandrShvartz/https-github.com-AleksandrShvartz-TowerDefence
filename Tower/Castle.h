#pragma once
#include "Header.h"
class Castle :
    public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    void setHealth(int);
    int getHealth();
    void  setPar(QString,int a, int b,int hel);
    //задаем область для перерисовки
    QRectF boundingRect() const override;
    //рисуем
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:
    int health=0;
    int w=0;
    int h=0;
    QString path=0;
};

