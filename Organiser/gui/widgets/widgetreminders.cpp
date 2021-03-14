#include "widgetreminders.h"
#include "ui_widgetreminders.h"

#include "cellnotes.h"
#include "gui/dialogs/dialogreminder.h"

WidgetReminders::WidgetReminders(QWidget *parent) :
	WidgetTab(size,parent),
	ui(new Ui::WidgetReminders)
{
	ui->setupUi(this);
}

WidgetReminders::~WidgetReminders()
{
	delete ui;
}

Reminders WidgetReminders::GetReminders()
{
	return reminders;
}

void WidgetReminders::SetAppData(AppData appData)
{
	this->appData = appData;
	this->reminders = appData.reminders;
}

void WidgetReminders::UpdateData(QDate date)
{
	//TODO:
	QList<Card> cards = calendar.GetCardsForDay(date,appData);

	ui->twdReminders->setRowCount(0);
	for(int i=0; i < cards.size();i++)
	{
		Card card = cards.at(i);
		addCardToListView(card,i);
	}


}

void WidgetReminders::addCardToListView(Card card, int id)
{
	ui->twdReminders->insertRow(0);

	CellNotes* cell = new CellNotes(card,id,ui->twdReminders);
	cell->SetDatesVisibility(false);
	ui->twdReminders->setCellWidget(0,0,cell);
}

void WidgetReminders::on_pushButton_clicked()
{
	DialogReminder dialogCard(this);

	if(dialogCard.exec() == QDialog::Accepted)
	{
		ReminderCard card = dialogCard.GetReminderCard();

		reminders.AddCard(card);

		emit reminderAdded();
	}
}
