#include "dialogcard.h"
#include "ui_dialogcard.h"



DialogCard::DialogCard(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogCard)
{
	ui->setupUi(this);
}

DialogCard::DialogCard(Card card, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogCard)
{
	ui->setupUi(this);

	this->card = card;
	setWidgetData(card);
	changeAcceptButtonToApply();
}

void DialogCard::setWidgetData(Card card)
{
	ui->tedTitle->setText(card.title);
	ui->tedDescription->setPlainText(card.description);

	ui->cbxPriority->setCurrentIndex((int)card.priority);
	ui->cbxStatus->setCurrentIndex((int)card.status);
}

void DialogCard::changeAcceptButtonToApply()
{
	ui->btnAccept->setText(tr("Accept"));
}

DialogCard::~DialogCard()
{
	delete ui;
}

Card DialogCard::GetCard()
{
	card.title = ui->tedTitle->text();
	card.description = ui->tedDescription->toPlainText();

	if(!card.creationDate.isValid())
	{
		card.creationDate = QDateTime::currentDateTime();
	}

	card.priority = (Card::Priority) ui->cbxPriority->currentIndex();

	Card::Status status = (Card::Status)ui->cbxStatus->currentIndex();
	card.status = status;

	if(status == Card::Status::Started)
	{
		card.finishedDate = QDateTime();
	}
	else
	{
		card.finishedDate = QDateTime::currentDateTime();
	}

	return card;
}

void DialogCard::on_btnAccept_clicked()
{
	accept();
}

void DialogCard::on_btnCancel_clicked()
{
	reject();
}
