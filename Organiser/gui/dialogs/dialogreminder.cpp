#include "dialogreminder.h"
#include "ui_dialogreminder.h"

DialogReminder::DialogReminder(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogReminder)
{
	ui->setupUi(this);
}

DialogReminder::DialogReminder(ReminderCard card,  QWidget *parent)  :
	DialogReminder(parent)
{
	this->card = card;
	setWidgetData(card);
	changeAcceptButtonToApply();
}

void DialogReminder::changeAcceptButtonToApply()
{
	ui->btnAccept->setText(tr("Accept"));
}

DialogReminder::~DialogReminder()
{
	delete ui;
}

void DialogReminder::on_btnAccept_clicked()
{
	accept();
}

void DialogReminder::on_btnCancel_clicked()
{
	reject();
}

void DialogReminder::setWidgetData(ReminderCard card)
{
	ui->tedTitle->setText(card.title);
	ui->dteStartTime->setDateTime(card.startDate);

	ui->cbxRepeat->setCurrentIndex((int)card.remindInterval);
}

ReminderCard DialogReminder::GetReminderCard()
{
	card.title = ui->tedTitle->text();
	card.startDate = ui->dteStartTime->dateTime();
	card.remindInterval = (RemindInterval)ui->cbxRepeat->currentIndex();

	return card;
}
