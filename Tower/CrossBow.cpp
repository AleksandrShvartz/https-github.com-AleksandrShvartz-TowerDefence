#include "CrossBow.h"

QRectF CrossBow::boundingRect() const
{
    return QRectF(-w,-h,w*3,h*3);
}

void CrossBow::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (path != 0) {
        //надо повернуть картинку (switch?)
        painter->drawImage(QRect(0,0,w,h),QImage(path));
    }
    else {
        
        if (!(angle < -M_PI / 3. && angle>-M_PI * 2 / 3.)) {
            oldAngle = angle;
        }
            painter->setBrush(QColor(105, 105, 105));
            QPen pen;
            QPolygonF arbalet;
            arbalet << QPointF(w / 2.-shirinaStvola, h) << QPointF(w / 2. + lengthOfBow * qCos(oldAngle)+shirinaStvola,h - lengthOfBow * qSin(oldAngle))
                << QPointF(w / 2., h) << QPointF(w / 2. + lengthOfBow * qCos(oldAngle), h - lengthOfBow * qSin(oldAngle)) << QPointF(w / 2. - shirinaStvola,h);
            pen.setWidth(3);
           // painter->drawLine(w / 2., h, w / 2. + lengthOfBow * qCos(angle), h - lengthOfBow * qSin(angle));
            painter->drawPolygon(arbalet);
         
            
        
    }
}

void  CrossBow::setPar(QString s, int a, int b, qreal ang,qreal old) {
    path = s;
    w = a;
    h = b;
    angle = ang;
    oldAngle = old;
}
void CrossBow::mouseMoveds(qreal newAngle,bool) {
    angle = newAngle;
  //  qDebug() << angle/M_PI;
    update();
}
