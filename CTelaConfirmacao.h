// "$Date: 2019-01-08 21:47:32 -0200 (ter, 08 jan 2019) $"
// "$Author: chico $"
// "$Revision: 3 $"

#ifndef CTELACONFIRMACAO_H
#define CTELACONFIRMACAO_H

#include "ui_CTelaConfirmacao.h"
#include <QPointF>

class QGraphicsSvgItem;
class QTimeLine;

#define BOTAO_OPACIDADE 0.65


class CTelaConfirmacao : public QWidget, private Ui::CTelaConfirmacao	{
	Q_OBJECT

public:
	explicit CTelaConfirmacao(QWidget *parent = 0);
	~CTelaConfirmacao();
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
};

#endif // CTELACONFIRMACAO_H
