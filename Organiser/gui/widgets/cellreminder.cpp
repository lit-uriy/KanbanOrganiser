#include "cellreminder.h"
#include "ui_cellreminder.h"

CellReminder::CellReminder(Card* card, int id, QWidget *parent)  :
	QWidget(parent),
	ui(new Ui::CellReminder)
{
	ui->setupUi(this);

	this->id = id;
	UpdateCard(card);
}

CellReminder::~CellReminder()
{
	delete ui;
}

void CellReminder::UpdateCard(Card* card)
{
	this->card = card;
	setWidgetData(card);
}

int CellReminder::GetId()
{
	return id;
}

Card CellReminder::GetCard()
{
	return card;
}

void CellReminder::setWidgetData(Card* card)
{
	ui->lblTitle->setText(card->title);

	ui->lblDescription->setText(card->description);

	setStartStatusIconAndLabel(card->startDate);

	setPriorityIcon(card->priority);

	bool isReminder = dynamic_cast<ReminderCard*>(card) != nullptr;

	setTypeIcon(isReminder);
}

void CellReminder::setStartStatusIconAndLabel(QDateTime startDate)
{
	if(startDate.isValid())
	{
		ui->wdtStartedTime->setVisible(true);
		QString date = startDate.toString("yyyy-MM-dd hh:mm");//TODO:
		ui->lblStartTime->setText(date);
		ui->lblStartTime->setToolTip(date);
	}
	else
	{
		ui->wdtStartedTime->setVisible(false);
	}
}

void CellReminder::setTypeIcon(bool isReminder)
{
	//TODO:Add Card Icon
	QString path = "";

	if(isReminder)
	{
		path = ":/icons/resources/icons/calendar.png";
	}
	else
	{
		path = ":/icons/resources/icons/board.png";
	}

	ui->imgType->setPixmap(QPixmap(path));
}

void CellReminder::setPriorityIcon(Card::Priority priority)
{
	QString path = "";

	switch(priority)
	{
		case Card::Priority::Low:
			path = ":/icons/resources/icons/priority_low.png";
			break;
		case Card::Priority::Medium:
			path = ":/icons/resources/icons/priority_mid.png";
			break;
		case Card::Priority::High:
			path = ":/icons/resources/icons/priority_high.png";
			break;
	}

	ui->imgPriority->setPixmap(QPixmap(path));
}
