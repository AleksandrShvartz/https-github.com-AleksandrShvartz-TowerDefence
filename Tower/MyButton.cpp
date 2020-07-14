#include "MyButton.h"
#include <QGraphicsSceneMouseEvent>
void MyButton::setPar(int a, int b, QString s)
{
    setAcceptHoverEvents(true);//��������� ��������� ��������� ���� 
    path = s;
    w = a;
    h = b;
    pauseClicked = false;
    hover = false;
}

QRectF MyButton::boundingRect() const
{        if(path=="pause")
    return QRectF(-w, 0, w*2, h*2);
else   return QRectF(0, 0, w, h );
}

void MyButton::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen;
    pen.setWidth(3);
    if (path !="pause"&&path!="play") {
        QImage im(path);
        painter->drawImage(QRectF(0, 0, w, h), im);
    }
    else {
        if (path == "pause") {
           
            pen.setColor(QColor(255, 215, 0));
            painter->setPen(pen);
            for(int i=1;i<30;i++)  
                if(i%2)
            painter->drawLine(QPointF(w / 2., h / 2.), QPointF(w*qCos(2*M_PI*i/30.)+ w / 2.,  h * qSin(2 * M_PI*i/30.)+h / 2.));
                else    painter->drawLine(QPointF(w / 2., h / 2.), QPointF(w *1.5* qCos(2 * M_PI * i / 30.) + w / 2., h *1.5* qSin(2 * M_PI * i / 30.) + h / 2.));
            painter->setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
            painter->drawEllipse(QRectF(0, 0, w, h));
           
            if (pauseClicked)
                painter->setBrush((QColor(128, 128, 128)));
            else
            painter->setBrush(QBrush(QColor(255, 140, 0), Qt::SolidPattern));
            painter->drawEllipse(QRectF(w/4, h/4, w/5, h/2));
            painter->drawEllipse(QRectF(w*5/8, h / 4, w / 5, h / 2));
        }
        else {
            pen.setColor(QColor(255, 0, 0));
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor(139,0,0), Qt::SolidPattern));
            painter->drawEllipse(QRectF(0, 0, w, h));
            QPolygon polygon; 
            painter->setBrush(Qt::black);
            polygon << QPoint(w/3, h/8) << QPoint(w/3, h*7/8) << QPoint(w*5/6, h/2);
            painter->drawPolygon(polygon);  
            if (hover) {
                QFont font;
                font.setBold(true);
                font.setPointSizeF(10);
                painter->setFont(font);
                painter->drawText(w * 8 / 20, h * 11 / 20, "PLAY");
            }
        }
    }
}

void MyButton::hoverEvent(qreal,bool b)
{
    if (path == "play") {
      //  qDebug() << "playHover";
        hover = b;
        update();
    }
 
}

void MyButton::mousePressEvent(QGraphicsSceneMouseEvent* apEvent)
{
    if (path == "pause") {
        pauseClicked = !pauseClicked;
        update();
    }
    emit btnMouseReleaseEvent(apEvent->button());
   

    qDebug() << "playPressed";
}
