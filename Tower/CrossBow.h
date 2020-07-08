#pragma once
#include <qgraphicsitem.h>
#include "Header.h"
class CrossBow :
    public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    void  setPar(QString, int a, int b, qreal ang,qreal old);
    //задаем область для перерисовки
    QRectF boundingRect() const override;
    //рисуем
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
public slots:
    void mouseMoveds(qreal,bool) ;
private:
    qreal angle;
    qreal oldAngle;
    int w = 0;
    int h = 0;
    QString path = 0;
};

