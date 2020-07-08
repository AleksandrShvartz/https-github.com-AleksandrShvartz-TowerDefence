#include "Arrow.h"

QRectF Arrow::boundingRect() const
{
	return QRectF(0,0,w,h);
}

void Arrow::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (path == 0) {
		painter->setBrush(QColor(0, 0, 0));
		painter->drawEllipse(0, 0, w, h);
	}
	else
	{
		painter->drawPixmap(QRect(0, 0, w, h), QPixmap(path));
	}
}/*
void Arrow::keyPressEvent(QKeyEvent* event)
{
	qDebug() << "ttt";
	if ((!timer.isActive())&&event->key() == Qt::Key_Space) {
		timer.start(1000);
		qDebug() << "yyy";
	}
}
void Arrow::timeIsOut()
{
	qDebug() << "jjj";
}
*/
 Arrow::Arrow(QString s, int a, int b, int dam, int x, int y, qreal angl) {
	path = s;
	w = a;
	h = b;
	coordX = x;
	coordY = y;
	angle = angl;
	damage = dam;
	inFly = false;
}
 
 void Arrow::setFly(bool b)
 {
	 inFly = b;
 }

 bool Arrow::getFly()
 {
	 return inFly;
 }
 void Arrow::setCoords(QPointF p)
 {
	 coordX = p.x();
	 coordY = p.y();
 }

 qreal Arrow::getAngle()
 {
	 return angle;
 }
 void Arrow::setAngle(qreal a)
 {
	 angle = a;
 }
 qreal Arrow::getConstAngle()
 {
	 return constAngle;
 }
 void Arrow::setConstAngle(qreal a)
 {
	 constAngle = a;
 }
 QPointF Arrow::getCoords()
 {
	 return QPointF(coordX, coordY);
 }
 Arrow::Arrow()  {
	 path =nullptr;
	 w = widthOfBorrow;
	 h = heightOfBorrow;
	 coordX = (((widthOfWindow - widthOfTower / 3.) / 2.) - widthOfBorrow) / 2.;
	 coordY = (heightOfWindow - heightOfTower - heightOfBow);
	 constAngle = M_PI / 2.;
	 damage = damageOfBorrow;
	// connect(&timer, SIGNAL(timeout),this,SLOT(timeIsOut));
 }
 void Arrow:: mmoveMouse(qreal an, bool)
 {
	 angle = an;
 }