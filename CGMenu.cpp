// "$Date: 2019-01-21 19:37:10 -0200 (seg, 21 jan 2019) $"
// "$Author: chico $"
// "$Revision: 72 $"

#include "CGMenu.h"
#include "CTelaConfirmacao.h"
#include "CQuickMenu.h"

#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QTransform>
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsItemGroup>
#include <QApplication>
#include <QTimeLine>
#include <QString>
#include <QPixmap>
#include <QTimer>

CGMenu::CGMenu(QWidget *parent) : QWidget(parent)	{
	setupUi(this);

	mScale = 1.0;
	mBaseSize = QSize(1200,960);
	mTime2 = 100;
	setCursor(QCursor(Qt::CrossCursor));


	mGS = new QGraphicsScene(this);
	gvMenu->setScene(mGS);
	gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPG/Fundo1")));

	mForm2 = new CTelaConfirmacao();
	mWidget2 = new QGraphicsProxyWidget();
	mWidget2->setWidget(mForm2);
	adjustScale(mWidget2, mForm2->background());
	mGS->addItem(mForm2->background());
	mGS->addItem(mWidget2);
	connect(cbMenu2Enabled, SIGNAL(toggled(bool)), this, SLOT(showMenu2(bool)));
	connect(mForm2->mTimeLine, SIGNAL(frameChanged(int)), this, SLOT(time2Changed(int)));

	mMenu4Estado = false;
	mForm4 = new CQuickMenu();
	mForm4->setVersion("iView Tecnologia Ind. e Com. Ltda.", "http://www.iviewtec.com.br", "suporte@iviewtec.com.br",
				QString::fromUtf8("Versão: %1 - %2").arg(REV_CODE).arg(QString(REV_SUBVN_DATE)));
	mWidget4 = new QGraphicsProxyWidget();
	mWidget4->setWidget(mForm4);
	adjustScale(mWidget4, mForm4->background());
	mGS->addItem(mForm4->background());
	mGS->addItem(mWidget4);
	connect(mForm4->mTimeLine, SIGNAL(frameChanged(int)), this, SLOT(time4Changed(int)));
	connect(mForm4, &CQuickMenu::signalShutDown, this, &CGMenu::close);

	mBackgroundChangeTimer = new QTimer(this);
	mBackgroundChangeTimer->setInterval(500);
	mBackgroundChangeTimer->setSingleShot(false);
	mBackgroundChangeTimer->start();
	connect (mBackgroundChangeTimer, SIGNAL(timeout()), this, SLOT(setNewBackgroud()));
	mBackgroundIndex = 1;
	//setGeometry(0,0,width(),height());

	showMenu2(false);
	cbMenu2Enabled->setChecked(false);
	showMenu4(false);
	// showMaximized();
	showFullScreen();
}

CGMenu::~CGMenu()	{
	mBackgroundChangeTimer->stop();
	disconnect (mBackgroundChangeTimer, SIGNAL(timeout()), this, SLOT(setNewBackgroud()));
	delete mBackgroundChangeTimer;

	disconnect(mForm2->mTimeLine, SIGNAL(frameChanged(int)), this, SLOT(time2Changed(int)));
	disconnect(mForm4->mTimeLine, SIGNAL(frameChanged(int)), this, SLOT(time4Changed(int)));
	disconnect(mForm4, &CQuickMenu::signalShutDown, this, &CGMenu::close);
	disconnect(cbMenu2Enabled, SIGNAL(toggled(bool)), this, SLOT(showMenu2(bool)));
	mGS->removeItem(mWidget2);
	mGS->removeItem(mWidget4);
	mWidget2->setWidget(nullptr);
	mWidget4->setWidget(nullptr);
	delete mWidget2;
	delete mWidget4;
	mGS->removeItem(mForm2->background());
	mGS->removeItem(mForm4->background());
	delete mForm2;
	delete mForm4;
	gvMenu->setScene(nullptr);
	delete mGS;
}

void CGMenu::setScale(int scale)	{
	qreal s = (qreal(scale))/100.0;
	gvMenu->setTransform(QTransform::fromScale(s, s));
	emit setZoom(s);
}

void CGMenu::adjustScale(QGraphicsProxyWidget * widget, QGraphicsSvgItem* item)	{
	qreal HScale = widget->boundingRect().width() /
				   item->boundingRect().width();
	qreal VScale = widget->boundingRect().height() /
				   item->boundingRect().height();
	if ( (HScale != 1.0) || (VScale != 1.0) )	{
		QTransform Transform;
		Transform.scale(HScale, VScale);
		item->setTransform(Transform);
	}
	// item->setPos(widget->mapToScene(widget->scenePos()));
	item->setPos(widget->scenePos());
}

void CGMenu::adjusttPos(QGraphicsProxyWidget * widget, QGraphicsSvgItem* item, QPointF basicPos, int time)	{
	qreal timeX, timeY;
	timeX = timeY = 0.0;
	if (basicPos.x() == 1.0)	{
		timeX = qreal(time) / 100.0 ;
		timeY = basicPos.y() ;
	}
	if (basicPos.x() == 0.0)	{
		timeX = 1.0 - qreal(time) / 100.0 ;
		timeY = basicPos.y() ;
	}
	if (basicPos.y() == 1.0)	{
		// timeX = basicPos.x();
		// timeY = qreal(time) / 100.0 ;
	}
	if (basicPos.y() == 0.0)	{
		timeX = basicPos.x() ;
		timeY = 1.0 - qreal(time) / 100.0 ;
	}

	// QSize lixo1 = gvMenu->size();
	// QSize lixo2 = widget->size().toSize();

	qreal X = gvMenu->size().width()  / mScale * basicPos.x() - widget->size().width()  * timeX - 5;
	qreal Y = gvMenu->size().height() / mScale * basicPos.y() - widget->size().height() * timeY - 2;

	widget->setPos(X, Y);
	item->setPos(X, Y);
}

void CGMenu::resizeEvent(QResizeEvent * /* event */)	{

	qreal Scale = 1.0;

	qreal ScaleByWidth = qreal(gvMenu->width()) / qreal(mBaseSize.width());

	qreal ScaleByHeight = qreal(gvMenu->height()) / qreal(mBaseSize.height());

	if (ScaleByHeight < ScaleByWidth)	{
		// height is the limiting factor
		Scale *= ScaleByHeight;
	} else {
		// width is the limiting factor
		Scale *= ScaleByWidth;
	}

	gvMenu->resetTransform();
	gvMenu->scale(Scale, Scale);
	mScale = Scale;

	adjusttPos(mWidget2, mForm2->background(), mForm2->basicPos(), mTime2);
	mGS->setSceneRect(0,0,(gvMenu->size().width()/mScale)-6, (gvMenu->size().height())/mScale-6);

}

void CGMenu::showMenu2(bool state)	{
	if (mForm2->mTimeLine->state() == QTimeLine::NotRunning)	{
		mForm2->mTimeLine->setDirection(state?QTimeLine::Forward: QTimeLine::Backward);
		mForm2->mTimeLine->start();
	}
}

void CGMenu::showMenu4(bool state)	{
	if (mForm4->mTimeLine->state() == QTimeLine::NotRunning)	{
		mForm4->mTimeLine->setDirection(state?QTimeLine::Forward: QTimeLine::Backward);
		mForm4->mTimeLine->start();
	}
}

void CGMenu::time2Changed(int time)	{
	mTime2 = time;
	adjusttPos(mWidget2, mForm2->background(), mForm2->basicPos(), mTime2);
}

void CGMenu::time4Changed(int time)	{
	mTime4 = time;
	adjusttPos(mWidget4, mForm4->background(), mForm4->basicPos(), mTime4);
}

void CGMenu::setNewBackgroud()	{
	switch (mBackgroundIndex)	{
		case 0:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_0")));
			break;
		case 1:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_1")));
			break;
		case 2:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_2")));
			break;
		case 3:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_3")));
			break;
		case 4:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_4")));
			break;
		case 5:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_5")));
			break;
		case 6:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_0")));
			break;
		case 7:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_1")));
			break;
		case 8:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_2")));
			break;
		case 9:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_3")));
			break;
		case 10:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_4")));
			break;
		case 11:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_5")));
			break;
		case 12:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig2_0")));
			break;
		case 13:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig2_1")));
			break;
		case 14:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig2_2")));
			break;
		case 15:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig2_3")));
			break;
		case 16:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig2_4")));
			break;
		case 17:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig2_5")));
			break;
		case 18:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig2_0")));
			break;
		case 19:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig2_1")));
			break;
		case 20:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig2_2")));
			break;
		case 21:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig2_3")));
			break;
		case 22:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig2_4")));
			break;
		case 23:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig2_5")));
			break;
		default:
			gvMenu->setBackgroundBrush(QPixmap(QString::fromUtf8(":/JPEG/fig1_0")));
	}
	mBackgroundIndex++;
	if (mBackgroundIndex >= 24)	mBackgroundIndex = 0;
}

void CGMenu::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)	{
		mMenu4Estado = ! mMenu4Estado;
		showMenu4(mMenu4Estado);
	}
	if (event->button() == Qt::RightButton)	{
		qApp->quit();
	}
	event->accept();
}
