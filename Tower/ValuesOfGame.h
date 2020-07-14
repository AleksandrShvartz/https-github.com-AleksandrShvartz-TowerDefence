#pragma once
#include "Header.h"

class ValuesOfGame :
    public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    void setPar(int s,int m,int  h,int poi,QString);
    void setPoints(int poi);
    void setRecords();
    void setNewRecords();
    int getPoints();
    void pauseTime(bool);
    //задаем область для перерисовки
    QRectF boundingRect() const override;
    //рисуем
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
 private slots:
    void refreshValues();
private:
    int timeS,recTimeS;
    int timeM,recTimeM;
    int timeH,recTimeH;
    int points,recPoints;
    QString path;
    QTimer time;
};

