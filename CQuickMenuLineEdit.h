// "$Date: 2019-01-22 12:20:56 -0200 (ter, 22 jan 2019) $"
// "$Author: chico $"
// "$Revision: 74 $"

#ifndef CQUICKMENULINEEDIT_H
#define CQUICKMENULINEEDIT_H

#include <QLineEdit>
#include <QTimer>

class QPushButton;

class CQuickMenuLineEdit : public QLineEdit	{
	Q_OBJECT
public:
	explicit CQuickMenuLineEdit(QWidget *parent = 0);
	void inserirBotoes(QPushButton * aumenta, QPushButton * diminui,
					   QPushButton * aceita, QPushButton * cancela);
	~CQuickMenuLineEdit();
	void mousePressEvent(QMouseEvent *);
	void ajustaValor(int novoValor);
	void ajustaMinimoMaximo(int minimo, int maximo);

private:
	void ajustaValor(bool positivo);

private:
	bool			mSelecionado;
	int				mValor;
	int				mValorProv;
	int				mMinimo;
	int				mMaximo;
	int				mIncremento;
	bool			mAumentar;	//	"true" se aumentar, "false" se diminuir;
	QTimer			* mTimer;
	QPushButton		* mBotAumenta;
	QPushButton		* mBotDiminui;
	QPushButton		* mBotAceita;
	QPushButton		* mBotCancela;

	enum Estagio {
		BASE = 1,
		CINCOS_1 = 2,
		CINCOS_2 = 3,
		DEZENAS_1 = 4,
		DEZENAS_2 = 5,
		CINCOENTAS_1 = 6,
		CINCOENTAS_2 = 7,
		CENTENAS_1 = 8,
		CENTENAS_2 = 9
	};

	Estagio			mEstagio;

public:
signals:
	void signalSelecionado();
	void signalNovoValor(int);

public slots:
	void slotAceitar();
	void slotRejeitar();
	void slotAumentar();
	void slotDiminuir();
	void slotCancelarIncremento();
	void slotTimeOutPressed();
	void slotTimeOutRepeat();

};

#endif // CQUICKMENULINEEDIT_H
