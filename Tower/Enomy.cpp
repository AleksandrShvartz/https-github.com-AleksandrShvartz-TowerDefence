#include "Enomy.h"
QRectF Enomy:: boundingRect() const {
	return QRectF(0,0,w,h);
}
void Enomy::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (path == 0) {
		switch (health)
		{
		case 20: {
			painter->setBrush(QColor(255, 0, 255));
			painter->drawEllipse(0, 0, w, h);
			painter->setBrush(QColor(128, 0, 0));
			painter->drawEllipse(w * 3 / 9., h * 2 / 9., w * 2 / 9., h * 2 / 9.);
			painter->drawEllipse(w * 5 / 9., h * 2 / 9., w * 2 / 9., h * 2 / 9.);
			painter->drawChord(w * 2 / 9., h * 5 / 9., 5 * w / 9., h * 2 / 9., 180 * 16, 225 * 16);
			break;
		}
		case 10: {
			painter->setBrush(QColor(128, 0, 128));
			painter->drawEllipse(0, 0, w, h);
			painter->setBrush(QColor(255, 0, 0));
			painter->drawEllipse(w * 3 / 9., h * 2 / 9., w * 2 / 9., h * 2 / 9.);
			painter->drawEllipse(w * 5 / 9., h * 2 / 9., w * 2 / 9., h * 2 / 9.);
			painter->drawChord(w * 2 / 9., h * 5 / 9., 5 * w / 9., h * 2 / 9., 180 * 16, 225 * 16);
			break;
		}
		default:
			break;
		}
		
	
	}
}

QPointF Enomy::getCoords()
{
	return QPointF(coordX,coordY);
}

void Enomy::setCoords(QPointF point)
{
	coordX = point.x();
	coordY = point.y();
}

void Enomy::setAng(qreal ang)
{
	angleOfEnomy = ang;
}

qreal Enomy::getAngl()
{
	return angleOfEnomy;
}

void Enomy::setHealth(int dam)
{
	health = dam;
}

int Enomy::getHealth()
{
	return health;
}
