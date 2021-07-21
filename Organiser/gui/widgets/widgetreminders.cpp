#include "widgetreminders.h"
#include "ui_widgetreminders.h"

#include "cellreminder.h"
#include "gui/dialogs/dialogreminder.h"

WidgetReminders::WidgetReminders(QWidget *parent) :
    WidgetTab(QSize(300,600),parent),
    size(QSize(300,600)),
    ui(new Ui::WidgetReminders)
{
    ui->setupUi(this);
}

WidgetReminders::~WidgetReminders()
{
    delete ui;
}

Reminders* WidgetReminders::GetReminders()
{
    return reminders;
}

void WidgetReminders::SetAppData(AppData* appData)
{
    this->appData = appData;
    calendar.SetAppData(appData);
    this->reminders = &appData->reminders;
}

void WidgetReminders::UpdateData(QDate date)
{
	this->date = date;

    QList<Card*> cards = calendar.GetCardsForDay(date);

    ui->twdReminders->setRowCount(0);
    for(int i=0; i < cards.size();i++)
    {
        Card* card = cards.at(i);
		addCardToListView(card,i,date);
    }


}

void WidgetReminders::addCardToListView(Card* card, int id,QDate date)
{
    ui->twdReminders->insertRow(0);

	CellReminder* cell = new CellReminder(card,id,date,ui->twdReminders);
    ui->twdReminders->setCellWidget(0,0,cell);
}

void WidgetReminders::on_pushButton_clicked()
{
	DialogReminder dialogCard(date,this);

    if(dialogCard.exec() == QDialog::Accepted)
    {
        ReminderCard* card = dialogCard.GetReminderCard();

        reminders->AddCard(card);

        emit reminderAdded();
    }
}

#include <QMenu>

void WidgetReminders::on_twdReminders_customContextMenuRequested(const QPoint &pos)
{
	QPoint position = ui->twdReminders->mapToGlobal(pos);

	if(ui->twdReminders->itemAt(position) == nullptr)
	{
		//return;
	}

	unsigned long long id = getSelectedCardID();

	if(id == 0)
	{
		return;
	}

    if(reminders->GetCard(id) == nullptr)
	{
		return;
	}

	QMenu menu;

	menu.addAction(ui->actionEditReminder);
	menu.addAction(ui->actionDeleteReminder);

	menu.exec(position);
}

void WidgetReminders::on_actionEditReminder_triggered()
{
	unsigned long long id = getSelectedCardID();

	if(id == 0)
	{
		return;
	}

    DialogReminder dialogCard(reminders->GetCard(id),this);


	if(dialogCard.exec() == QDialog::Accepted)
	{
		ReminderCard* card = dialogCard.GetReminderCard();
        reminders->ReplaceCard(id,card);
		replaceSelectedCard(card);

		emit reminderAdded();
	}
}
unsigned long long WidgetReminders::getSelectedCardID()
{
	CellReminder* cellReminder = getSelectedCell();

	return cellReminder->GetId();
}

CellReminder* WidgetReminders::getSelectedCell()
{
	int row = getSelectedCellIndex();

	if(row == -1)
	{
		return nullptr;
	}

	return dynamic_cast<CellReminder*>(ui->twdReminders->cellWidget(row,0));
}


int WidgetReminders::getSelectedCellIndex()
{
	QItemSelectionModel *select = ui->twdReminders->selectionModel();

	QModelIndexList indexlist = select->selectedRows();

	if(indexlist.size() == 0)
	{
		return -1;
	}

	QModelIndex index = indexlist.first();
	int row = index.row();

	return row;
}

void WidgetReminders::replaceSelectedCard(Card* card)
{
	CellReminder* cell = getSelectedCell();
	cell->UpdateCard(card);
}

void WidgetReminders::on_actionDeleteReminder_triggered()
{

	unsigned long long id = getSelectedCardID();
	deleteCard(id);
	emit reminderAdded();
}

void WidgetReminders::deleteCard(unsigned long long id)
{
	if(id == 0)
	{
		return;
	}

    reminders->DeleteCard(id);
	UpdateData(date);

	emit reminderAdded();
}
