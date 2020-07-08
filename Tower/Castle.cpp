#include "Castle.h"

QRectF Castle::boundingRect() const
{
	return QRectF(0,0,w,h);
}

void Castle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (path == 0) {
		QPen pen;
		pen.setWidth(2);
		pen.setColor(QColor(139, 69, 19));
		painter->setPen(pen);
		painter->setBrush(QColor(139, 69, 19));
		painter->drawRect( 0, h*2/7., w / 6.,h*5/7.);
		painter->drawRect(w/6, h*4/7., w / 6., h*3 / 7.);
		painter->drawRect(w / 3., 0, w / 3., h );
		painter->drawRect(w*2 / 3., h * 4 / 7., w / 6., h * 3 / 7.);
		painter->drawRect(w*5/6., h * 2 / 7., w / 6., h * 5 / 7.);
		painter->setBrush(QColor(205, 133, 63));
		painter->drawEllipse(w * 5 / 30., h* 5/7., w * 20 / 30., h * 6 / 7.);
		pen.setColor(Qt::black);
		pen.setWidth(1);
		painter->setBrush(Qt::black);
		pen.setBrush(Qt::black);
		painter->drawLine(w * 11 / 12., h * 2 / 7., w * 11 / 12., h*3 / 14.);
		painter->setBrush(Qt::red);
		painter->drawRect(w * 11 / 12., h*3 / 14.,w/12.,h/28.);

	}
	else {
		painter->drawImage(QRect(0,0,w,h),QImage(path));
	}
}
int Castle::getHealth()
{
	return health;
}
void Castle:: setHealth(int a) {
	health= a;
}
void Castle:: setPar(QString s, int a, int b, int hel)
{
	path = s;
	w = a;
	h = b;
	health = hel;
}