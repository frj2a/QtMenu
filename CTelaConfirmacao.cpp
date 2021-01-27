// "$Date: 2019-01-08 21:47:32 -0200 (ter, 08 jan 2019) $"
// "$Author: chico $"
// "$Revision: 3 $"

#include "CTelaConfirmacao.h"
#include <QGraphicsSvgItem>
#include <QTimeLine>

CTelaConfirmacao::CTelaConfirmacao(QWidget *parent) :	QWidget(parent)		{
	setupUi(this);
	mBasePos = QPointF(0.5 , 0.0);	// numbers meaning percent of screen
	mTimeLine = new QTimeLine(500, this);
	mTimeLine->setCurveShape(QTimeLine::EaseInOutCurve);
	mTimeLine->setFrameRange(0,100);
	mBackground = new QGraphicsSvgItem(":/SVG/FundoTelaConfirmacao");
	mBackground->setOpacity(0.50);
	mOpacidade = BOTAO_OPACIDADE;
	// setOpacity(mOpacidade);
}

CTelaConfirmacao::~CTelaConfirmacao()	{
	delete mBackground;
}

void CTelaConfirmacao::changeEvent(QEvent *e)	{
	QWidget::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			retranslateUi(this);
			break;
		default:
			break;
	}
}
