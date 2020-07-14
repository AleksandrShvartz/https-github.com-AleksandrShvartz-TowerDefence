#include "MyView.h"
#include "Header.h"

MyView::MyView()
{	  
	gameStarted = false;
	estSnariad = false;
	//сглаживаем примитивы
	setRenderHint(QPainter::Antialiasing);
	//устанавливаем бэкграунд
	
	this->setBackgroundBrush(QBrush(Qt::blue)/*QPixmap("C:\\Users\\Vladimir_Shvartc\\Downloads\\fire.jpg")*/);
	setCacheMode(QGraphicsView::CacheNone);
	//отключаем возможность прокрутки
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setWindowTitle("Tower");
	//убираем отступы
	setFrameStyle(0);
	//устанавливаем размер сцены и виджета и убираем возможность менять размер окна
	setSceneRect(0, 0, widthOfWindow, heightOfWindow);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	setFixedSize(widthOfWindow, heightOfWindow);
	//т к у нас много движущихся объектов индексирование не нужно, ибо замедляет анимацию
	scene.setItemIndexMethod(QGraphicsScene::NoIndex);
	initElements();
	setScene(&scene);
	setMouseTracking(true);
	connect(this, &MyView::mouseMoved, &btnPlay,&MyButton::hoverEvent);
	connect(&btnPlay, &MyButton::btnMouseReleaseEvent, this, &MyView::btnPlayClicked);
	connect(&timer2, &QTimer::timeout, this, &MyView::createEnomy);
	connect(&timer, &QTimer::timeout, this, &MyView::refreshTime);
	mediaOfShot	 = new QMediaPlayer;
	mediaOfShot->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("C:\\Users\\Vladimir_Shvartc\\Downloads\\16557_1460656892.mp3")));
	mediaOfScream = new QMediaPlayer;
	mediaOfScream->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("C:\\Users\\Vladimir_Shvartc\\Downloads\\414209__jacksonacademyashmore__death.wav")));
	mediaOfShot->setVolume(50);
	mediaOfHit = new QMediaPlayer;
	mediaOfHit->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("C:\\Users\\Vladimir_Shvartc\\Downloads\\135936__bradwesson__collectcoin.wav")));
	mediaOfEnd = new QMediaPlayer;
	mediaOfEnd->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("C:\\Users\\Vladimir_Shvartc\\Downloads\\253886__themusicalnomad__negative-beeps.wav")));
	mediaOfDeath = new QMediaPlayer;
	mediaOfDeath->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("C:\\Users\\Vladimir_Shvartc\\Downloads\\107789__leviclaassen__hit-002.wav")));
	mediaOfCreate = new QMediaPlayer;
	mediaOfCreate->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("C:\\Users\\Vladimir_Shvartc\\Downloads\\195568__jacobalcook__creature-roar-1.wav")));
}		  

void MyView::startGame()
{
	
	onPause = false;
	timer.start(50);
	timer2.start(3000);
	
	//connect(this, &MyView::sendTorefreshValues, &borrows, &Arrow::refreshCoords);
	connect(this,&MyView::mouseMoved,&bow, &CrossBow::mouseMoveds);
	btnPause.setPar(widthOfBtnPause, heightOfBtnPause, "pause"/*"C:\\Users\\Vladimir_Shvartc\\Downloads\\pause.png"*/);
	btnPause.setPos(widthOfWindow - widthOfBtnPause, 0);
	scene.addItem(&btnPause);
	connect(&btnPause, &MyButton::btnMouseReleaseEvent, this, &MyView::btnPauseClicked);
	gameStarted = true;
	scene.removeItem(&btnPlay);
	tower.setPar(0/**/, widthOfTower, heightOfTower, heathOfTower);
	tower.setPos((widthOfWindow-widthOfTower)/2.,(heightOfWindow-heightOfTower));
	scene.addItem(&tower);
	bow.setPar(0/*?*/, widthOfBow, heightOfBow, M_PI / 2.,M_PI/2.);
	bow.setPos((widthOfWindow - widthOfTower / 3.) / 2., (heightOfWindow - heightOfTower-heightOfBow));
	scene.addItem(&bow);
	reload();

	bowX= (widthOfWindow - widthOfBorrow) / 2.;
	bowY= (heightOfWindow - heightOfTower - heightOfBow);
	arrows[arrows.size() - 1]->setCoords(QPointF(bowX, bowY));
	bowAngle = M_PI / 2.;
	arrows[arrows.size() - 1]->setConstAngle(bowAngle);

	val = new ValuesOfGame;
	val->setPar(0, 0, 0, heathOfTower,/**/0);
	val->setPos(widthOfWindow * 3 / 4., 0);
	scene.addItem(val);
	update();
}

void MyView::pauseGame()
{
	if (!onPause)
		timer2.stop();
	else timer2.start(3000);
	onPause = !onPause;

}

void MyView::endOfTheGame()
{
	if (gameStarted) {
		while (arrows.size() > 0) {
			int i = arrows.size() - 1;
			scene.removeItem(arrows[i]);
			delete[] arrows[i];
			arrows.removeAt(i);
		}
		while (vragi.size() > 0) {
			int i = vragi.size() - 1;
			scene.removeItem(vragi[i]);
			delete[] vragi[i];
			vragi.removeAt(i);
		}
		scene.removeItem(&btnPause);
		scene.removeItem(&tower);
		scene.removeItem(&bow);
		delete val;
		timer2.stop();
		timer.stop();
		gameStarted = false;
		initElements();
	}
	//startGame();
}

void MyView::mouseMoveEvent(QMouseEvent* event)
{
	if (!onPause) {
		//qDebug() << "take angle";
		QPointF coordMouse = event->pos();
		int x0 = (widthOfWindow - widthOfTower / 3.) / 2. + widthOfBow / 2.;
		int y0 = (heightOfWindow - heightOfTower - heightOfBow) + heightOfBow;
		qreal angle;
		if (coordMouse.y() <= y0)
			angle = qAcos((coordMouse.x() - x0) / qSqrt((coordMouse.x() - x0) * (coordMouse.x() - x0) + (coordMouse.y() - y0) * (coordMouse.y() - y0)));
		else angle = -qAcos((coordMouse.x() - x0) / qSqrt((coordMouse.x() - x0) * (coordMouse.x() - x0) + (coordMouse.y() - y0) * (coordMouse.y() - y0)));
		bool in = (coordMouse.x() >= (widthOfWindow - widthOfBtnPlay) / 2. && coordMouse.x() <= (widthOfWindow + widthOfBtnPlay) / 2.
			&& coordMouse.y() >= (heightOfWindow - heightOfBtnPlay) / 2. && coordMouse.y() <= (heightOfWindow + heightOfBtnPlay) / 2.);
		emit mouseMoved(angle, in);
		if (gameStarted) {
			if (!(angle < -M_PI / 3. && angle>-M_PI * 2 / 3.) && !arrows[arrows.size() - 1]->getFly()) {
				arrows[arrows.size() - 1]->setPos(QPointF(widthOfBow / 2. + lengthOfBow * qCos(angle) + (widthOfWindow - widthOfTower / 3.) / 2. - widthOfBorrow / 2.,
					(heightOfWindow - heightOfBorrow / 2. - heightOfTower - heightOfBow) + heightOfBow - lengthOfBow * qSin(angle)));
				int arrowX = widthOfBow / 2. + lengthOfBow * qCos(angle) + (widthOfWindow - widthOfTower / 3.) / 2. - widthOfBorrow / 2.;
				int arrowY = (heightOfWindow - heightOfBorrow / 2. - heightOfTower - heightOfBow) + heightOfBow - lengthOfBow * qSin(angle);
				arrows[arrows.size() - 1]->setCoords(QPointF(arrowX, arrowY));
				arrows[arrows.size() - 1]->setAngle(angle);
			}
			if (!(angle < -M_PI / 3. && angle>-M_PI * 2 / 3.)) {
				bowX = widthOfBow / 2. + lengthOfBow * qCos(angle) + (widthOfWindow - widthOfTower / 3.) / 2. - widthOfBorrow / 2.;
				bowY = (heightOfWindow - heightOfBorrow / 2. - heightOfTower - heightOfBow) + heightOfBow - lengthOfBow * qSin(angle);
				bowAngle = angle;
			}
		}
	}
}

void MyView::keyPressEvent(QKeyEvent* event)
{
	if (!onPause&&gameStarted) {
		if (event->key() == Qt::Key_Space) {
			if (arrows.size() <= capasityOfQuiver) {
				arrows[arrows.size() - 1]->setFly(true);
				arrows[arrows.size() - 1]->setConstAngle(arrows[arrows.size() - 1]->getAngle());
				if (mediaOfShot->state() == QMediaPlayer::PlayingState) {
					mediaOfShot->stop();
				}
				mediaOfShot->play();
				reload();
				qDebug() << "fly" << arrows[arrows.size() - 1]->getAngle();
			}
		}
	}
}

MyView::~MyView()
{
	endOfTheGame();
	delete mediaOfCreate;
	delete mediaOfDeath;
	delete mediaOfEnd;
	delete mediaOfHit;
	delete mediaOfShot;
	delete mediaOfScream;
}

void MyView::initElements()
{
	
	btnPlay.setPar(widthOfBtnPlay, heightOfBtnPlay,"play"/* "C:\\Users\\Vladimir_Shvartc\\Downloads\\playbtn.jpg"*/);
	btnPlay.setPos((widthOfWindow-widthOfBtnPlay)/2.,(heightOfWindow-heightOfBtnPlay)/2.);
	scene.addItem(&btnPlay);
	
}

void MyView::reload()
{
	
		arrows.push_back(new Arrow());
		connect(this, &MyView::mouseMoved, (arrows[arrows.size() - 1]), &Arrow::mmoveMouse);
		//arrows[arrows.size() - 1]->setPos((widthOfWindow - widthOfBorrow) / 2., (heightOfWindow - heightOfTower - heightOfBow));
		scene.addItem(arrows[arrows.size() - 1]);
		arrows[arrows.size() - 1]->setFly(false);
		arrows[arrows.size() - 1]->setAngle(bowAngle);
		arrows[arrows.size() - 1]->setCoords(QPointF(bowX, bowY));
		arrows[arrows.size() - 1]->setPos(bowX, bowY);
	
}



void MyView::refreshTime()
{
	if (!onPause) {
		for (int i = 0; i < arrows.size(); i++) {
			if (arrows[i]->getFly()) {
				int xxx = arrows[i]->getCoords().x();
				int yyy = arrows[i]->getCoords().y();
				xxx += speedOfArrow * qCos(arrows[i]->getConstAngle());
				yyy -= speedOfArrow * qSin(arrows[i]->getConstAngle());
				qDebug() << xxx << " " << yyy << " " << arrows[i]->getConstAngle() / M_PI;
				if (xxx >= 0 && xxx <= widthOfWindow && yyy >= 0 && yyy <= heightOfWindow) {
					arrows[i]->setPos(xxx, yyy);
					arrows[i]->setCoords(QPointF(xxx, yyy));
				}
				else {
					scene.removeItem(arrows[i]);
					delete[]  arrows[i];
					arrows.removeAt(i);
					i--;
				}
			}
		}

		for (int i = 0; i < vragi.size(); i++) {
			vragi[i]->setCoords(QPointF(vragi[i]->getCoords().x() + speedOfEnomy * qCos(vragi[i]->getAngl()),
				vragi[i]->getCoords().y() - speedOfEnomy * qSin(vragi[i]->getAngl())));
			vragi[i]->setPos(QPointF(vragi[i]->getCoords().x() + speedOfEnomy * qCos(vragi[i]->getAngl()),
				vragi[i]->getCoords().y() - speedOfEnomy * qSin(vragi[i]->getAngl())));
			if (vragi[i]->collidesWithItem(&tower)) {
				tower.setHealth(tower.getHealth()-damageOfEnomy);
				
				
				scene.removeItem(&*vragi[i]);
				delete[] 	vragi[i];
				vragi.removeAt(i);
				i--;
				if (tower.getHealth() <= 0) {
					mediaOfEnd->play();
					endOfTheGame();
					qDebug() << "Game Over";
				} else mediaOfScream->play();
				break;
				update();
			}
			for (int j = 0; j < arrows.size(); j++)
				if (vragi[i]->collidesWithItem(arrows[j])) {
				//	if(arrows[j]->getFly())
					scene.removeItem(arrows[j]);
					
					delete[]  arrows[j];
					arrows.removeAt(j);
					j--;
					vragi[i]->setHealth(vragi[i]->getHealth()-damageOfBorrow);
					
					if (vragi[i]->getHealth() <= 0) {
						mediaOfDeath->play();
						scene.removeItem(&*vragi[i]);
						delete[] 	vragi[i];
						vragi.removeAt(i);
						i--;
						break;
					}	else mediaOfHit->play();
				}

		}

		//emit sendTorefreshValues();
		update();
		//qDebug() << "timeStarted";
	}
}

void MyView::createEnomy()
{
	mediaOfCreate->play();
	qDebug() << "createEnomy";
	int storona =Random::get(1,2);	
//if (countOfEnomy+1 <= 10) {
	vragi.push_back(new Enomy());
		int xx, yy;
		if (storona==1)
			xx = 0;
		else
			xx = widthOfWindow - widthOfEnomy;
		yy = Random::get(0, heightOfWindow - heigthOfEnomy);
		qDebug() << xx << " " << yy;
		
		(vragi[vragi.size() - 1])->setPos(xx, yy);
		QPointF center(widthOfWindow / 2., heightOfWindow/2.);
		qreal ang;
		if(yy>=center.y())
		ang= qAcos((center.x() - xx) / qSqrt((center.x() - xx) * (center.x() - xx) + (center.y() - yy) * (center.y() - yy)));
		else ang = -qAcos((center.x() - xx) / qSqrt((center.x() - xx) * (center.x() - xx) + (center.y() - yy) * (center.y() - yy)));
		(vragi[vragi.size() - 1])->setCoords(QPointF(xx, yy));
		(vragi[vragi.size() - 1])->setAng(ang);
		scene.addItem((vragi[vragi.size() - 1]));
		qDebug()<<"monster" << ang / M_PI<<" "<<vragi.size();
	//}
}


void MyView::btnPlayClicked(Qt::MouseButton button)
{
   qDebug() << "gameStarted";
	startGame();
	
}
void  MyView::btnPauseClicked(Qt::MouseButton) {
	qDebug() << "gamePaused";
	if (gameStarted) {
		pauseGame();
	   }
}
