#pragma once
#include "Header.h"

class ValuesOfGame :
    public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    void setPar(int s,int m,int  h,int hel,QString);
    //задаем область для перерисовки
    QRectF boundingRect() const override;
    //рисуем
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
 private slots:
    void refreshValues();
private:
    int timeS;
    int timeM;
    int timeH;
    int health;
    QString path;
    QTimer time;
};

