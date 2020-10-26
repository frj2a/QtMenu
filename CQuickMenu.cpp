// "$Date: 2019-01-22 12:20:56 -0200 (ter, 22 jan 2019) $"
// "$Author: chico $"
// "$Revision: 74 $"

#include "CQuickMenu.h"
#include <QGraphicsSvgItem>
#include <QTimeLine>
#include <QIcon>
#include <QPixmap>
#include <QPalette>

CQuickMenu::CQuickMenu(QWidget *parent) : QWidget(parent)	{
	setupUi(this);
	mBasePos = QPointF(0.0 , 1.0);	// numbers meaning percent of screen
	mTimeLine = new QTimeLine(1000, this);
	mTimeLine->setCurveShape(QTimeLine::EaseInOutCurve);
	mTimeLine->setFrameRange(0,100);
	mBackground = new QGraphicsSvgItem();
	mBackground->setOpacity(0.30);
	frameLens->hide();
	frameMovement->hide();
	frameImage->hide();
	frameTools->hide();
	frameSettings->hide();
	frameAdjust->hide();
	frameAbout->hide();
	pbAumenta->hide();
	pbDiminui->hide();
	pbAceita->hide();
	pbCancela->hide();
	pbShutDown->setChecked(false);
	pbLens->setChecked(false);
	pbMovement->setChecked(false);
	pbImage->setChecked(false);
	pbTools->setChecked(false);
	pbSettings->setChecked(false);
	connect(pbShutDown, &QPushButton::clicked, this, &CQuickMenu::signalShutDown);
	connect(mTimeLine, SIGNAL(finished()), this, SLOT(hideAll()));
	mOpacidade = BOTAO_OPACIDADE;

	edIntervalo->inserirBotoes(pbAumenta, pbDiminui, pbAceita, pbCancela);
	edIntervalo->ajustaMinimoMaximo(250,2000);
	edVelocidadeVertical->inserirBotoes(pbAumenta, pbDiminui, pbAceita, pbCancela);
	edVelocidadeVertical->ajustaMinimoMaximo(1, 1000);
	edQuantidadePulsos->inserirBotoes(pbAumenta, pbDiminui, pbAceita, pbCancela);
	edQuantidadePulsos->ajustaMinimoMaximo(2, 4000);
	edQtdAquisicoes->inserirBotoes(pbAumenta, pbDiminui, pbAceita, pbCancela);
	edQtdAquisicoes->ajustaMinimoMaximo(1, 10);
	edVelocidadeMotor->inserirBotoes(pbAumenta, pbDiminui, pbAceita, pbCancela);
	edVelocidadeMotor->ajustaMinimoMaximo(0, 100);
	edNitidez->inserirBotoes(pbAumenta, pbDiminui, pbAceita, pbCancela);
	edNitidez->ajustaMinimoMaximo(0, 100);

	//	edIntervalo
	connect(edIntervalo, SIGNAL(signalSelecionado()), edVelocidadeVertical, SLOT(slotRejeitar()));
	connect(edIntervalo, SIGNAL(signalSelecionado()), edQuantidadePulsos, SLOT(slotRejeitar()));
	connect(edIntervalo, SIGNAL(signalSelecionado()), edQtdAquisicoes, SLOT(slotRejeitar()));
	connect(edIntervalo, SIGNAL(signalSelecionado()), edVelocidadeMotor, SLOT(slotRejeitar()));
	connect(edIntervalo, SIGNAL(signalSelecionado()), edNitidez, SLOT(slotRejeitar()));

	//	edVelocidadeVertical
	connect(edVelocidadeVertical, SIGNAL(signalSelecionado()), edIntervalo, SLOT(slotRejeitar()));
	connect(edVelocidadeVertical, SIGNAL(signalSelecionado()), edQuantidadePulsos, SLOT(slotRejeitar()));
	connect(edVelocidadeVertical, SIGNAL(signalSelecionado()), edQtdAquisicoes, SLOT(slotRejeitar()));
	connect(edVelocidadeVertical, SIGNAL(signalSelecionado()), edVelocidadeMotor, SLOT(slotRejeitar()));
	connect(edVelocidadeVertical, SIGNAL(signalSelecionado()), edNitidez, SLOT(slotRejeitar()));

	// edQuantidadePulsos
	connect(edQuantidadePulsos, SIGNAL(signalSelecionado()), edIntervalo, SLOT(slotRejeitar()));
	connect(edQuantidadePulsos, SIGNAL(signalSelecionado()), edVelocidadeVertical, SLOT(slotRejeitar()));
	connect(edQuantidadePulsos, SIGNAL(signalSelecionado()), edQtdAquisicoes, SLOT(slotRejeitar()));
	connect(edQuantidadePulsos, SIGNAL(signalSelecionado()), edVelocidadeMotor, SLOT(slotRejeitar()));
	connect(edQuantidadePulsos, SIGNAL(signalSelecionado()), edNitidez, SLOT(slotRejeitar()));

	// edQtdAquisicoes
	connect(edQtdAquisicoes, SIGNAL(signalSelecionado()), edIntervalo, SLOT(slotRejeitar()));
	connect(edQtdAquisicoes, SIGNAL(signalSelecionado()), edVelocidadeVertical, SLOT(slotRejeitar()));
	connect(edQtdAquisicoes, SIGNAL(signalSelecionado()), edQuantidadePulsos, SLOT(slotRejeitar()));
	connect(edQtdAquisicoes, SIGNAL(signalSelecionado()), edVelocidadeMotor, SLOT(slotRejeitar()));
	connect(edQtdAquisicoes, SIGNAL(signalSelecionado()), edNitidez, SLOT(slotRejeitar()));

	// edVelocidadeMotor
	connect(edVelocidadeMotor, SIGNAL(signalSelecionado()), edIntervalo, SLOT(slotRejeitar()));
	connect(edVelocidadeMotor, SIGNAL(signalSelecionado()), edVelocidadeVertical, SLOT(slotRejeitar()));
	connect(edVelocidadeMotor, SIGNAL(signalSelecionado()), edQuantidadePulsos, SLOT(slotRejeitar()));
	connect(edVelocidadeMotor, SIGNAL(signalSelecionado()), edQtdAquisicoes, SLOT(slotRejeitar()));
	connect(edVelocidadeMotor, SIGNAL(signalSelecionado()), edNitidez, SLOT(slotRejeitar()));

	// edNitidez
	connect(edNitidez, SIGNAL(signalSelecionado()), edIntervalo, SLOT(slotRejeitar()));
	connect(edNitidez, SIGNAL(signalSelecionado()), edVelocidadeVertical, SLOT(slotRejeitar()));
	connect(edNitidez, SIGNAL(signalSelecionado()), edQuantidadePulsos, SLOT(slotRejeitar()));
	connect(edNitidez, SIGNAL(signalSelecionado()), edQtdAquisicoes, SLOT(slotRejeitar()));
	connect(edNitidez, SIGNAL(signalSelecionado()), edVelocidadeMotor, SLOT(slotRejeitar()));
}

CQuickMenu::~CQuickMenu()	{
	//	edIntervalo
	disconnect(edIntervalo, SIGNAL(signalSelecionado()), edVelocidadeVertical, SLOT(slotRejeitar()));
	disconnect(edIntervalo, SIGNAL(signalSelecionado()), edQuantidadePulsos, SLOT(slotRejeitar()));
	disconnect(edIntervalo, SIGNAL(signalSelecionado()), edQtdAquisicoes, SLOT(slotRejeitar()));
	disconnect(edIntervalo, SIGNAL(signalSelecionado()), edVelocidadeMotor, SLOT(slotRejeitar()));
	disconnect(edIntervalo, SIGNAL(signalSelecionado()), edNitidez, SLOT(slotRejeitar()));

	//	edVelocidadeVertical
	disconnect(edVelocidadeVertical, SIGNAL(signalSelecionado()), edIntervalo, SLOT(slotRejeitar()));
	disconnect(edVelocidadeVertical, SIGNAL(signalSelecionado()), edQuantidadePulsos, SLOT(slotRejeitar()));
	disconnect(edVelocidadeVertical, SIGNAL(signalSelecionado()), edQtdAquisicoes, SLOT(slotRejeitar()));
	disconnect(edVelocidadeVertical, SIGNAL(signalSelecionado()), edVelocidadeMotor, SLOT(slotRejeitar()));
	disconnect(edVelocidadeVertical, SIGNAL(signalSelecionado()), edNitidez, SLOT(slotRejeitar()));

	// edQuantidadePulsos
	disconnect(edQuantidadePulsos, SIGNAL(signalSelecionado()), edIntervalo, SLOT(slotRejeitar()));
	disconnect(edQuantidadePulsos, SIGNAL(signalSelecionado()), edVelocidadeVertical, SLOT(slotRejeitar()));
	disconnect(edQuantidadePulsos, SIGNAL(signalSelecionado()), edQtdAquisicoes, SLOT(slotRejeitar()));
	disconnect(edQuantidadePulsos, SIGNAL(signalSelecionado()), edVelocidadeMotor, SLOT(slotRejeitar()));
	disconnect(edQuantidadePulsos, SIGNAL(signalSelecionado()), edNitidez, SLOT(slotRejeitar()));

	// edQtdAquisicoes
	disconnect(edQtdAquisicoes, SIGNAL(signalSelecionado()), edIntervalo, SLOT(slotRejeitar()));
	disconnect(edQtdAquisicoes, SIGNAL(signalSelecionado()), edVelocidadeVertical, SLOT(slotRejeitar()));
	disconnect(edQtdAquisicoes, SIGNAL(signalSelecionado()), edQuantidadePulsos, SLOT(slotRejeitar()));
	disconnect(edQtdAquisicoes, SIGNAL(signalSelecionado()), edVelocidadeMotor, SLOT(slotRejeitar()));
	disconnect(edQtdAquisicoes, SIGNAL(signalSelecionado()), edNitidez, SLOT(slotRejeitar()));

	// edVelocidadeMotor
	disconnect(edVelocidadeMotor, SIGNAL(signalSelecionado()), edIntervalo, SLOT(slotRejeitar()));
	disconnect(edVelocidadeMotor, SIGNAL(signalSelecionado()), edVelocidadeVertical, SLOT(slotRejeitar()));
	disconnect(edVelocidadeMotor, SIGNAL(signalSelecionado()), edQuantidadePulsos, SLOT(slotRejeitar()));
	disconnect(edVelocidadeMotor, SIGNAL(signalSelecionado()), edQtdAquisicoes, SLOT(slotRejeitar()));
	disconnect(edVelocidadeMotor, SIGNAL(signalSelecionado()), edNitidez, SLOT(slotRejeitar()));

	// edNitidez
	disconnect(edNitidez, SIGNAL(signalSelecionado()), edIntervalo, SLOT(slotRejeitar()));
	disconnect(edNitidez, SIGNAL(signalSelecionado()), edVelocidadeVertical, SLOT(slotRejeitar()));
	disconnect(edNitidez, SIGNAL(signalSelecionado()), edQuantidadePulsos, SLOT(slotRejeitar()));
	disconnect(edNitidez, SIGNAL(signalSelecionado()), edQtdAquisicoes, SLOT(slotRejeitar()));
	disconnect(edNitidez, SIGNAL(signalSelecionado()), edVelocidadeMotor, SLOT(slotRejeitar()));

	disconnect(mTimeLine, SIGNAL(finished()), this, SLOT(hideAll()));
	delete mBackground;
}

void CQuickMenu::changeEvent(QEvent *e)	{
	QWidget::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			retranslateUi(this);
			break;
		default:
			break;
	}
}

void CQuickMenu::setVersion(QString companyName, QString homePage, QString supportContact, QString version)	{
	labelCompany->setText(companyName);
	labelHomePage->setText(homePage);
	labelSupport->setText(supportContact);
	labelVersion->setText(version);
}

void CQuickMenu::on_pbLens_clicked(bool status) {
	if (status) {
		frameLens->show();
	} else {
		frameLens->hide();
	}
	if (status && pbMovement->isChecked()) {
		pbMovement->setChecked(false);
		frameMovement->hide();
	}
	if (status && pbImage->isChecked()) {
		pbImage->setChecked(false);
		frameImage->hide();
	}
	if (status && pbTools->isChecked()) {
		pbTools->setChecked(false);
		frameTools->hide();
	}
	if (status && pbSettings->isChecked()) {
		pbSettings->setChecked(false);
		frameSettings->hide();
		frameAdjust->hide();
		pbAumenta->hide();
		pbDiminui->hide();
		pbAceita->hide();
		pbCancela->hide();
	}
	if (status && pbAbout->isChecked()) {
		pbAbout->setChecked(false);
		frameAbout->hide();
	}
}

void CQuickMenu::on_pbMovement_clicked(bool status)	{
	if (status) {
		frameMovement->show();
	} else {
		frameMovement->hide();
	}
	if (status && pbLens->isChecked())	{
		pbLens->setChecked(false);
		frameLens->hide();
	}
	if (status && pbImage->isChecked())	{
		pbImage->setChecked(false);
		frameImage->hide();
	}
	if (status && pbTools->isChecked())	{
		pbTools->setChecked(false);
		frameTools->hide();
	}
	if (status && pbSettings->isChecked())	{
		pbSettings->setChecked(false);
		frameSettings->hide();
		frameAdjust->hide();
		pbAumenta->hide();
		pbDiminui->hide();
		pbAceita->hide();
		pbCancela->hide();
	}
	if (status && pbAbout->isChecked()) {
		pbAbout->setChecked(false);
		frameAbout->hide();
	}
}

void CQuickMenu::on_pbImage_clicked(bool status)	{
	if (status) {
		frameImage->show();
	} else {
		frameImage->hide();
	}
	if (status && pbLens->isChecked())	{
		pbLens->setChecked(false);
		frameLens->hide();
	}
	if (status && pbMovement->isChecked())	{
		pbMovement->setChecked(false);
		frameMovement->hide();
	}
	if (status && pbTools->isChecked())	{
		pbTools->setChecked(false);
		frameTools->hide();
	}
	if (status && pbSettings->isChecked())	{
		pbSettings->setChecked(false);
		frameSettings->hide();
		frameAdjust->hide();
		pbAumenta->hide();
		pbDiminui->hide();
		pbAceita->hide();
		pbCancela->hide();
	}
	if (status && pbAbout->isChecked()) {
		pbAbout->setChecked(false);
		frameAbout->hide();
	}
}

void CQuickMenu::on_pbTools_clicked(bool status)	{
	if (status) {
		frameTools->show();
	} else {
		frameTools->hide();
	}
	if (status && pbLens->isChecked())	{
		pbLens->setChecked(false);
		frameLens->hide();
	}
	if (status && pbMovement->isChecked())	{
		pbMovement->setChecked(false);
		frameMovement->hide();
	}
	if (status && pbImage->isChecked())	{
		pbImage->setChecked(false);
		frameImage->hide();
	}
	if (status && pbSettings->isChecked())	{
		pbSettings->setChecked(false);
		frameSettings->hide();
		frameAdjust->hide();
		pbAumenta->hide();
		pbDiminui->hide();
		pbAceita->hide();
		pbCancela->hide();
	}
	if (status && pbAbout->isChecked()) {
		pbAbout->setChecked(false);
		frameAbout->hide();
	}
}

void CQuickMenu::on_pbSettings_clicked(bool status)	{
	if (status) {
		frameSettings->show();
		frameAdjust->show();
		pbAumenta->show();
		pbDiminui->show();
		pbAceita->show();
		pbCancela->show();
	} else {
		frameSettings->hide();
		frameAdjust->hide();
		pbAumenta->hide();
		pbDiminui->hide();
		pbAceita->hide();
		pbCancela->hide();
	}
	if (status && pbLens->isChecked())	{
		pbLens->setChecked(false);
		frameLens->hide();
	}
	if (status && pbMovement->isChecked())	{
		pbMovement->setChecked(false);
		frameMovement->hide();
	}
	if (status && pbImage->isChecked())	{
		pbImage->setChecked(false);
		frameImage->hide();
	}
	if (status && pbTools->isChecked())	{
		pbTools->setChecked(false);
		frameTools->hide();
	}
	if (status && pbAbout->isChecked()) {
		pbAbout->setChecked(false);
		frameAbout->hide();
	}
}

void CQuickMenu::on_pbAbout_clicked(bool status) {
	if (status) {
		frameAbout->show();
	} else {
		frameAbout->hide();
	}
	if (status && pbLens->isChecked())	{
		pbLens->setChecked(false);
		frameLens->hide();
	}
	if (status && pbMovement->isChecked())	{
		pbMovement->setChecked(false);
		frameMovement->hide();
	}
	if (status && pbImage->isChecked())	{
		pbImage->setChecked(false);
		frameImage->hide();
	}
	if (status && pbTools->isChecked())	{
		pbTools->setChecked(false);
		frameTools->hide();
	}
	if (status && pbSettings->isChecked())	{
		pbSettings->setChecked(false);
		frameSettings->hide();
		frameAdjust->hide();
		pbAumenta->hide();
		pbDiminui->hide();
		pbAceita->hide();
		pbCancela->hide();
	}

}

void CQuickMenu::hideAll() {
	if (pbLens->isChecked()) {
		pbLens->setChecked(false);
		frameLens->hide();
	}
	if (pbMovement->isChecked()) {
		pbMovement->setChecked(false);
		frameMovement->hide();
	}
	if (pbImage->isChecked()) {
		pbImage->setChecked(false);
		frameImage->hide();
	}
	if (pbTools->isChecked()) {
		pbTools->setChecked(false);
		frameTools->hide();
	}
	if (pbSettings->isChecked()) {
		pbSettings->setChecked(false);
		frameSettings->hide();
		frameAdjust->hide();
		pbAumenta->hide();
		pbDiminui->hide();
		pbAceita->hide();
		pbCancela->hide();
	}
	if (pbAbout->isChecked()) {
		pbAbout->setChecked(false);
		frameAbout->hide();
	}
}

void CQuickMenu::buttonClicked()	{

}
