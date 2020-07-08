#pragma once
#include <QGraphicsItem>
#include "Header.h"
#include <QPainter>
#include <QDebug>
//#include <qurl.h>
//#include <QWidget>
//#include <QStyleOptionGraphicsItem>
class MyButton :
   public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
  void  setPar(int a, int b, QString s);
    //задаем область для перерисовки
    QRectF boundingRect() const override;
    //рисуем
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
signals:
    void btnMouseReleaseEvent(Qt::MouseButton);
public slots:
    void hoverEvent(qreal,bool) ;
  //  void hoverLeaveEvent(qreal,QGraphicsSceneHoverEvent*) ;
private:
    int h=0;
    int w=0;
    QString path=0;
    bool hover = false;
    bool pauseClicked = false;;
};

