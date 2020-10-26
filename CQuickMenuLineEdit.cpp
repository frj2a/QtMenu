// "$Date: 2019-01-22 12:20:56 -0200 (ter, 22 jan 2019) $"
// "$Author: chico $"
// "$Revision: 74 $"

#include "CQuickMenuLineEdit.h"
#include <QPushButton>
#include <QMouseEvent>
#if defined(_DEBUG)
#  include <iostream>
#endif

#define POSITIVO	true
#define NEGATIVO	false

CQuickMenuLineEdit::CQuickMenuLineEdit(QWidget *parent) : QLineEdit(parent)	{
	mSelecionado = false;
	mValor = text().toInt();
	mBotAumenta = NULL;
	mBotDiminui = NULL;
	mBotAceita  = NULL;
	mBotCancela = NULL;
	mEstagio = BASE;
	mIncremento = 1;
	mTimer = new QTimer(this);
	mTimer->setInterval(800);
	mTimer->setSingleShot(true);
	mTimer->stop();
}

void CQuickMenuLineEdit::inserirBotoes(QPushButton * aumenta,
									   QPushButton * diminui,
									   QPushButton * aceita,
									   QPushButton * cancela)	{
	mBotAumenta = aumenta;
	mBotDiminui = diminui;
	mBotAceita  = aceita;
	mBotCancela = cancela;
	mEstagio = BASE;
	mIncremento = 1;


	mMinimo = 1;
	int maxlen = maxLength();
	switch (maxlen) {
	case 1:
		mMaximo = 9;
		break;
	case 2:
		mMaximo = 99;
		break;
	case 3:
		mMaximo = 999;
		break;
	case 4:
		mMaximo = 9999;
		break;
	default:
		mMaximo = 9999;
		break;
	}
}

CQuickMenuLineEdit::~CQuickMenuLineEdit()	{
	disconnect(mBotAceita, &QPushButton::clicked, this, &CQuickMenuLineEdit::slotAceitar);
	disconnect(mBotCancela, &QPushButton::clicked, this, &CQuickMenuLineEdit::slotRejeitar);
	disconnect(mBotAumenta, &QPushButton::pressed, this, &CQuickMenuLineEdit::slotAumentar);
	disconnect(mBotDiminui, &QPushButton::pressed, this, &CQuickMenuLineEdit::slotDiminuir);
	disconnect(mBotAumenta, &QPushButton::released, this, &CQuickMenuLineEdit::slotCancelarIncremento);
	disconnect(mBotDiminui, &QPushButton::released, this, &CQuickMenuLineEdit::slotCancelarIncremento);
}

void CQuickMenuLineEdit::mousePressEvent(QMouseEvent *evento)	{
	mEstagio = BASE;
	mIncremento = 1;
	if (evento->button() == Qt::LeftButton)	{
		if (!mSelecionado)	{
			mSelecionado = true;
			mValor = text().toInt();
			connect(mBotAceita, &QPushButton::clicked, this, &CQuickMenuLineEdit::slotAceitar);
			connect(mBotCancela, &QPushButton::clicked, this, &CQuickMenuLineEdit::slotRejeitar);
			connect(mBotAumenta, &QPushButton::pressed, this, &CQuickMenuLineEdit::slotAumentar);
			connect(mBotDiminui, &QPushButton::pressed, this, &CQuickMenuLineEdit::slotDiminuir);
			connect(mBotAumenta, &QPushButton::released, this, &CQuickMenuLineEdit::slotCancelarIncremento);
			connect(mBotDiminui, &QPushButton::released, this, &CQuickMenuLineEdit::slotCancelarIncremento);
			setStyleSheet((QString)"background-image:url();background-color:rgb(0,255,0);");
			emit signalSelecionado();
		}
	}
}

void CQuickMenuLineEdit::ajustaValor(int novoValor) {
	mValor = mValorProv = novoValor;
	setText(QString::number(novoValor));
}

void CQuickMenuLineEdit::ajustaMinimoMaximo(int minimo, int maximo) {
	mMinimo = minimo;
	mMaximo = maximo;
}

void CQuickMenuLineEdit::slotAceitar()	{
	setStyleSheet((QString)"background-image: url();background-color:rgb(255,255,255);");
	mSelecionado = false;
	mValor = text().toInt();
	disconnect(mBotAceita, &QPushButton::clicked, this, &CQuickMenuLineEdit::slotAceitar);
	disconnect(mBotCancela, &QPushButton::clicked, this, &CQuickMenuLineEdit::slotRejeitar);
	disconnect(mBotAumenta, &QPushButton::pressed, this, &CQuickMenuLineEdit::slotAumentar);
	disconnect(mBotDiminui, &QPushButton::pressed, this, &CQuickMenuLineEdit::slotDiminuir);
	disconnect(mBotAumenta, &QPushButton::released, this, &CQuickMenuLineEdit::slotCancelarIncremento);
	disconnect(mBotDiminui, &QPushButton::released, this, &CQuickMenuLineEdit::slotCancelarIncremento);
	mEstagio = BASE;
	mIncremento = 1;
	emit signalNovoValor(mValor);
}

void CQuickMenuLineEdit::slotRejeitar()	{
	if (mSelecionado)	{
		setStyleSheet((QString)"background-image: url();background-color:rgb(255,255,255);");
		mSelecionado = false;
		setText(QString::number(mValor));
		disconnect(mBotAceita, &QPushButton::clicked, this, &CQuickMenuLineEdit::slotAceitar);
		disconnect(mBotCancela, &QPushButton::clicked, this, &CQuickMenuLineEdit::slotRejeitar);
		disconnect(mBotAumenta, &QPushButton::pressed, this, &CQuickMenuLineEdit::slotAumentar);
		disconnect(mBotDiminui, &QPushButton::pressed, this, &CQuickMenuLineEdit::slotDiminuir);
		disconnect(mBotAumenta, &QPushButton::released, this, &CQuickMenuLineEdit::slotCancelarIncremento);
		disconnect(mBotDiminui, &QPushButton::released, this, &CQuickMenuLineEdit::slotCancelarIncremento);
	}
	mEstagio = BASE;
	mIncremento = 1;
}

void CQuickMenuLineEdit::slotAumentar()	{
	mAumentar = true;
	mTimer->setSingleShot(true);
	mTimer->setInterval(800);
	connect(mTimer, &QTimer::timeout, this, &CQuickMenuLineEdit::slotTimeOutPressed);
	mTimer->start();
	ajustaValor(mAumentar);
}

void CQuickMenuLineEdit::slotDiminuir()	{
	mAumentar = false;
	mTimer->setSingleShot(true);
	mTimer->setInterval(800);
	connect(mTimer, &QTimer::timeout, this, &CQuickMenuLineEdit::slotTimeOutPressed);
	mTimer->start();
	ajustaValor(mAumentar);
}

void CQuickMenuLineEdit::ajustaValor(bool positivo) {
	mValorProv = text().toInt();
	if ( (mValorProv >= mMinimo) && (mValorProv < mMaximo) ) {
		switch (mEstagio) {
		case BASE:
			if ( (mValorProv % 5) == 0) {
				mEstagio = CINCOS_1;
				mIncremento = 1;
			}
			break;
		case CINCOS_1:
			if ( (mValorProv % 5) == 0) {
				mEstagio = CINCOS_2;
				mIncremento = 5;
			} else {
				mIncremento = 1;
			}
			break;
		case CINCOS_2:
			if ( (mValorProv % 10) == 0) {
				mEstagio = DEZENAS_1;
				mIncremento = 5;
			}
			break;
		case DEZENAS_1:
			if ( (mValorProv % 10) == 0) {
				mEstagio = DEZENAS_2;
				mIncremento = 10;
			} else {
				mIncremento = 5;
			}
			break;
		case DEZENAS_2:
			if ( (mValorProv % 50) == 0) {
				mEstagio = CINCOENTAS_1;
				mIncremento = 10;
			}
			break;
		case CINCOENTAS_1:
			if ( (mValorProv % 50) == 0) {
				mEstagio = CINCOENTAS_2;
				mIncremento = 50;
			} else {
				mIncremento = 10;
			}
			break;
		case CINCOENTAS_2:
			if ( (mValorProv % 100) == 0) {
				mEstagio = CENTENAS_1;
				mIncremento = 50;
			}
			break;
		case CENTENAS_1:
			if ( (mValorProv % 100) == 0) {
				mEstagio = CENTENAS_1;
				mIncremento = 100;
			} else {
				mIncremento = 50;
			}
			break;
		default:
			break;
		}
	}
#if defined(_DEBUG)
	// std::cout << mEstagio << " " << mValorProv << " - " << mMaximo << std::endl;
#endif
	if (positivo) {
		if (mValorProv + mIncremento <= mMaximo) {
			mValorProv += mIncremento;
		} else {
			mValorProv = mMaximo;
		}
	} else {
		if ( (mValorProv - mIncremento) >= mMinimo) {
			mValorProv -= mIncremento;
		} else {
			mValorProv = mMinimo;
		}
	}
	setText(QString::number(mValorProv));
}

void CQuickMenuLineEdit::slotTimeOutPressed() {
	disconnect(mTimer, &QTimer::timeout, this, &CQuickMenuLineEdit::slotTimeOutPressed);
	connect(mTimer, &QTimer::timeout, this, &CQuickMenuLineEdit::slotTimeOutRepeat);
	mTimer->setSingleShot(false);
	mTimer->setInterval(333);
	ajustaValor(mAumentar);
	mTimer->start();
}

void CQuickMenuLineEdit::slotTimeOutRepeat() {
	ajustaValor(mAumentar);
}

void CQuickMenuLineEdit::slotCancelarIncremento() {
	mTimer->stop();
	disconnect(mTimer, &QTimer::timeout, this, &CQuickMenuLineEdit::slotTimeOutRepeat);
	mTimer->setSingleShot(true);
	mTimer->stop();
	mEstagio = BASE;
	mIncremento = 1;
}
