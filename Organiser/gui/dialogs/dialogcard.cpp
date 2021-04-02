#include "dialogcard.h"
#include "ui_dialogcard.h"



DialogCard::DialogCard(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogCard)
{
	ui->setupUi(this);
	setDefaultDeadline();
	ui->cbxHasDeadline->setChecked(false);
	setDeadlineEnabled(false);
}

DialogCard::DialogCard(Card* card, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogCard)
{
	ui->setupUi(this);

	setWidgetData(card);
	changeAcceptButtonToApply();
}

void DialogCard::setWidgetData(Card* card)
{
	ui->tedTitle->setText(card->title);
	ui->tedDescription->setPlainText(card->description);

	ui->cbxPriority->setCurrentIndex((int)card->priority);
	ui->cbxStatus->setCurrentIndex((int)card->status);

	if(card->startDate.isValid())
	{
		setDeadlineEnabled(true);
		ui->cbxHasDeadline->setChecked(true);
		ui->dteStartTime->setDateTime(card->startDate);

		ui->dteDeadline->setDateTime(card->deadline);
		ui->dteDeadline->setMinimumDateTime(ui->dteStartTime->dateTime());
	}
	else
	{
		setDeadlineEnabled(false);
		ui->cbxHasDeadline->setChecked(false);
		setDefaultDeadline();
	}

}


void DialogCard::setDefaultDeadline()
{
	ui->dteStartTime->setDateTime(QDateTime::currentDateTime());

	ui->dteDeadline->setDateTime(QDateTime::currentDateTime().addDays(1));
	ui->dteDeadline->setMinimumDateTime(ui->dteStartTime->dateTime());
}

void DialogCard::changeAcceptButtonToApply()
{
	ui->btnAccept->setText(tr("Accept"));
}

DialogCard::~DialogCard()
{
	delete ui;
}

Card* DialogCard::GetCard()
{
	Card* card = new Card();
	card->title = ui->tedTitle->text();
	card->description = ui->tedDescription->toPlainText();

	if(!card->creationDate.isValid())
	{
		card->creationDate = QDateTime::currentDateTime();
	}

	card->priority = (Card::Priority) ui->cbxPriority->currentIndex();

	Card::Status status = (Card::Status)ui->cbxStatus->currentIndex();
	card->status = status;

	if(status == Card::Status::Started)
	{
		card->finishedDate = QDateTime();
	}
	else
	{
		card->finishedDate = QDateTime::currentDateTime();
	}

	if(ui->cbxHasDeadline->isChecked())
	{
		card->startDate = ui->dteStartTime->dateTime();
		card->deadline = ui->dteDeadline->dateTime();
	}
	else
	{
		card->startDate = QDateTime();
		card->deadline = QDateTime();
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

void DialogCard::on_cbxHasDeadline_clicked(bool checked)
{
	setDeadlineEnabled(checked);
}

void DialogCard::setDeadlineEnabled(bool enabled)
{
	ui->dteStartTime->setEnabled(enabled);
	ui->dteDeadline->setEnabled(enabled);
}

void DialogCard::on_dteStartTime_dateTimeChanged(const QDateTime &dateTime)
{
	ui->dteDeadline->setMinimumDateTime(ui->dteStartTime->dateTime());
}
