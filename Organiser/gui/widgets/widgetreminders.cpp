#include "widgetreminders.h"
#include "ui_widgetreminders.h"

#include "cellnotes.h"

WidgetReminders::WidgetReminders(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::WidgetReminders)
{
	ui->setupUi(this);
}

WidgetReminders::~WidgetReminders()
{
	delete ui;
}

void WidgetReminders::SetAppData(AppData appData)
{
	this->appData = appData;
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
