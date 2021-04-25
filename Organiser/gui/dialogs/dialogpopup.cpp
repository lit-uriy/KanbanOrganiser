#include "dialogpopup.h"
#include "ui_dialogpopup.h"

#include "datastructures/reminders/remindercard.h"

DialogPopup::DialogPopup(ReminderCard* card,QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogPopup)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

	ui->wdtCard->UpdateCard(card);
    updateButtonVisibility(card);
}

void DialogPopup::updateButtonVisibility(ReminderCard* card)
{
    bool isReminder = dynamic_cast<ReminderCard*>(card) != nullptr;

    ui->btnMarkAsFinished->setVisible(isReminder);
}

DialogPopup::~DialogPopup()
{
	delete ui;
}

unsigned long long DialogPopup::GetCardId()
{
	return ui->wdtCard->GetId();
}

void DialogPopup::closeEvent(QCloseEvent* event)
{
	emit closed(this);
	QWidget::closeEvent(event);
}

void DialogPopup::on_btnMarkAsFinished_clicked()
{
	emit markAsFinished(this);
	close();
}

void DialogPopup::on_btnPostpone_clicked()
{
	int minutes = 1;
	//TODO:Dialog to pick time
	emit postpone(this,minutes);
	close();
}
