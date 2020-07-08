#include "ValuesOfGame.h"

QRectF ValuesOfGame::boundingRect() const
{
	return QRectF(0,0,widthOfValues,heightOfValues);
}

void ValuesOfGame::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	pen.setColor(Qt::black);
	pen.setWidth(70);
	painter->setPen(pen);
	//pen.setCapStyle();
	painter->drawText(0, heightOfValues / 2, QString("time of survive is ") + QString::number(timeH) + QString(':') + QString::number(timeM) + QString(':') + QString::number(timeS));
}
void ValuesOfGame::setPar(int s, int m, int  h, int hel,QString p) {
	timeS = s;
	timeM = m;
	timeH = h;
	health = hel;
	path = p;
	time.start(1000);
	connect(&time, &QTimer::timeout, this, &ValuesOfGame::refreshValues);
}

void ValuesOfGame::refreshValues()
{
	qDebug() << "time++";
	timeS++;
	if (timeS == 60) {
		timeS = 0;
		timeM++;
		if (timeM == 60) {
			timeM = 0;
			timeH++;
		}
	}
	update();
}
