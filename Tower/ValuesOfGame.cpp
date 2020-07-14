#include "ValuesOfGame.h"

void ValuesOfGame::setPoints(int poi)
{
	points = poi;
}

void ValuesOfGame::setRecords()
{
	QFile fileIn("C:\\Users\\Vladimir_Shvartc\\source\\repos\\Tower\\Tower\\records.txt");
	if (fileIn.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream in(&fileIn);
		int tmp[4];	int i = 0;
		while (!in.atEnd()) {
			QString str = in.readLine();
			QTextStream strStream(&str);
			strStream >> tmp[i];
				i++;
		}
		recTimeS=tmp[0];
		recTimeM = tmp[1];
		recTimeH = tmp[2];
		recPoints = tmp[3];
		fileIn.close();
	}
	else qDebug() << "error fileOpen(in)";
	
}

void ValuesOfGame::setNewRecords()
{
	if (recPoints < points) {
		QFile fileOut("C:\\Users\\Vladimir_Shvartc\\source\\repos\\Tower\\Tower\\records.txt");
		if (fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QTextStream out(&fileOut);
			out << timeS << '\n' << timeM << '\n' << timeH << '\n' << points;
			fileOut.close();
		}
		else qDebug() << "error fileOpen(out)";
	}
}

int ValuesOfGame::getPoints()
{
	return points;
}

void ValuesOfGame::pauseTime(bool b)
{
	if (b)time.stop();
	else time.start(1000);
}

QRectF ValuesOfGame::boundingRect() const
{
	return QRectF(0,0,widthOfValues*3,heightOfValues);
}

void ValuesOfGame::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	pen.setColor(Qt::green);
	pen.setWidth(7);
	painter->setPen(pen);
	//pen.setCapStyle();
	painter->drawText(widthOfValues*3/2., heightOfValues /2, QString("Time of survive is ") + QString::number(timeH) + QString(':')
		+ QString::number(timeM) + QString(':') + QString::number(timeS)+ QString(" Points: ")+ QString::number(points));
	painter->drawText(0, heightOfValues / 2, QString("Record time is ") + QString::number(recTimeH) + QString(':')
		+ QString::number(recTimeM) + QString(':') + QString::number(recTimeS) + QString(" Record points: ") + QString::number(recPoints));
}
void ValuesOfGame::setPar(int s, int m, int  h, int poi,QString p) {
	timeS = s;
	timeM = m;
	timeH = h;
	points = poi;
	path = p;
	time.start(1000);
	connect(&time, &QTimer::timeout, this, &ValuesOfGame::refreshValues);
	setRecords();
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
