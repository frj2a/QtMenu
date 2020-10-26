// "$Date: 2019-01-08 21:47:32 -0200 (ter, 08 jan 2019) $"
// "$Author: chico $"
// "$Revision: 3 $"

#include "QGraphicsButtonItem.h"
#include <QGraphicsSvgItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QTextDocument>
#include <QSvgRenderer>


QGraphicsButtonItem::QGraphicsButtonItem(QString svgButton, QString label,
										 QColor labelColor)	{
	mButtonNormal = new QSvgRenderer(svgButton, this);
	mButtonPressed = new QSvgRenderer(QString(svgButton + "_pressed"), this);
	mButtonDisabled = new QSvgRenderer(QString(svgButton + "_disabled"), this);
	mButton = new QGraphicsSvgItem();
	mButton->setSharedRenderer(mButtonNormal);
	mLabel = new QGraphicsTextItem(label, this);
	mLabelColor = labelColor;
	mLabel->setDefaultTextColor(mLabelColor);
	addToGroup(mButton);
	addToGroup(mLabel);
	qreal wLabel = mLabel->boundingRect().width();
	qreal hLabel = mLabel->boundingRect().height();
	qreal wButton = mButton->boundingRect().width();
	qreal hButton = mButton->boundingRect().height();
	mLabel->setPos(mButton->pos().x() + (wButton - wLabel) / 2.0,
				   mButton->pos().y() + (hButton - hLabel) / 2.0 );
	mEffect = new QGraphicsDropShadowEffect(this);
	mLabel->setGraphicsEffect(mEffect);
	mEffect->setOffset(0.75);
	mEnabled = true;
}

QGraphicsButtonItem::~QGraphicsButtonItem()	{
	if (mLabel != NULL)	{
		removeFromGroup(mLabel);
		delete mEffect;
		delete mLabel;
	}
	if (mButton != NULL)	{
		removeFromGroup(mButton);
		delete mButtonNormal;
		delete mButtonPressed;
		delete mButtonDisabled;
		delete mButton;
	}
}

void QGraphicsButtonItem::mousePressEvent(QGraphicsSceneMouseEvent * event)	{
	if ( (event->button() == Qt::LeftButton) && mEnabled )	{
		emit clicked();
		mButton->setSharedRenderer(mButtonPressed);
	}
}

void QGraphicsButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)	{
	if ( (event->button() == Qt::LeftButton) && mEnabled )	{
		mButton->setSharedRenderer(mButtonNormal);
	}
}

void QGraphicsButtonItem::zoomChanged(qreal zoom)	{	// SLOT
	mEffect->setOffset(0.75 * zoom);
}

void QGraphicsButtonItem::enabledChanged(bool enabled)	{	// SLOT
	mEnabled = enabled;
	if (mEnabled)	{
		mButton->setSharedRenderer(mButtonNormal);
		mLabel->setDefaultTextColor(mLabelColor);
	} else {
		mButton->setSharedRenderer(mButtonDisabled);
		mLabel->setDefaultTextColor(Qt::white);
	}
}
