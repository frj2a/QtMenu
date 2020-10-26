// "$Date: 2019-01-08 21:47:32 -0200 (ter, 08 jan 2019) $"
// "$Author: chico $"
// "$Revision: 3 $"

#ifndef QGRAPHICSBUTTONITEM_H
#define QGRAPHICSBUTTONITEM_H

#include <QColor>
#include <QGraphicsItemGroup>

class QSvgRenderer;
class QGraphicsSvgItem;
class QGraphicsTextItem;
class QGraphicsDropShadowEffect;

class QGraphicsButtonItem : public QObject, public QGraphicsItemGroup	{
	Q_OBJECT
public:
	QGraphicsButtonItem(QString svgButton, QString label, QColor labelColor);
	~QGraphicsButtonItem();

private:
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
	QWidget						* mParent;
	QGraphicsSvgItem			* mButton;
	QSvgRenderer				* mButtonNormal;
	QSvgRenderer				* mButtonPressed;
	QSvgRenderer				* mButtonDisabled;
	QGraphicsTextItem			* mLabel;
	QGraphicsDropShadowEffect	* mEffect;
	QColor						mLabelColor;
	bool						mEnabled;

public:
signals:
	void clicked();

public
slots:
	void zoomChanged(qreal);
	void enabledChanged(bool);

};

#endif // QGRAPHICSBUTTONITEM_H
