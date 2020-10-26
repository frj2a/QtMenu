// "$Date: 2019-01-21 16:55:46 -0200 (seg, 21 jan 2019) $"
// "$Author: chico $"
// "$Revision: 67 $"

#ifndef CQUICKMENU_H
#define CQUICKMENU_H

#include "ui_CQuickMenu.h"
#include <QPointF>

class QGraphicsSvgItem;
class QTimeLine;

#define BOTAO_OPACIDADE 0.65


class CQuickMenu : public QWidget, private Ui::CQuickMenu	{
	Q_OBJECT

public:
	explicit CQuickMenu(QWidget *parent = 0);
	~CQuickMenu();
	QGraphicsSvgItem * background()	{	return mBackground;	}
	QPointF basicPos()				{	return mBasePos;	}

private:
	QGraphicsSvgItem	* mBackground;
	QPointF				mBasePos;
	qreal				mOpacidade;

public:
	QTimeLine			* mTimeLine;

protected:
	void changeEvent(QEvent *e);

public:
	void setVersion(QString companyName, QString homePage, QString supportContact, QString version);

public
slots:
	void on_pbLens_clicked(bool);
	void on_pbMovement_clicked(bool);
	void on_pbImage_clicked(bool);
	void on_pbSettings_clicked(bool);
	void on_pbTools_clicked(bool);
	void on_pbAbout_clicked(bool);
	void hideAll();
	void buttonClicked();

public:
signals:
	void signalShutDown();

};

#endif // CQUICKMENU_H
