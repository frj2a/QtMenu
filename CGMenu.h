// "$Date: 2019-01-21 19:37:10 -0200 (seg, 21 jan 2019) $"
// "$Author: chico $"
// "$Revision: 72 $"

#ifndef CGMENU_H
#define CGMENU_H

#include "ui_CGMenu.h"
#include <QWidget>
#include <QSize>

class QTimer;
class QGraphicsScene;
class QGraphicsSvgItem;
class QGraphicsProxyWidget;

class CTelaMenu;
class CTelaConfirmacao;
class CMainMenu;
class CQuickMenu;

class CGMenu : public QWidget, public Ui::CGMenu
{
	Q_OBJECT

public:
	explicit CGMenu(QWidget *parent = 0);
	~CGMenu();
	void resizeEvent(QResizeEvent * event);
	void mousePressEvent(QMouseEvent * event);

private:
	qreal					mScale;
	QSize					mBaseSize;
	QTimer					* mBackgroundChangeTimer;

	QGraphicsScene			* mGS;

	CTelaConfirmacao		* mForm2;
	QGraphicsProxyWidget	* mWidget2;
	int						mTime2;

	CQuickMenu				* mForm4;
	QGraphicsProxyWidget	* mWidget4;
	int						mTime4;
	bool					mMenu4Estado;

	int						mBackgroundIndex;

private:
	void adjustScale(QGraphicsProxyWidget *widget, QGraphicsSvgItem* item);
	void adjusttPos(QGraphicsProxyWidget * widget, QGraphicsSvgItem* item, QPointF basicPos, int time);


public
slots:
	void setScale(int);
	void setNewBackgroud();
	void showMenu2(bool state);
	void showMenu4(bool state);
	void time2Changed(int time);
	void time4Changed(int time);

public:
signals:
	void setZoom(qreal);

};

#endif // CGMENU_H
