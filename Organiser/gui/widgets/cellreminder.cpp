#include "cellreminder.h"
#include "ui_cellreminder.h"

CellReminder::CellReminder(Card* card, int id,QDate date, QWidget *parent)  :
	QWidget(parent),
	ui(new Ui::CellReminder)
{
	ui->setupUi(this);

	this->date = date;
	UpdateCard(card);
}

CellReminder::~CellReminder()
{
	delete ui;
}

void CellReminder::UpdateCard(Card* card)
{
	setWidgetData(card);
}

unsigned long long CellReminder::GetId()
{
	return id;
}

void CellReminder::setWidgetData(Card* card)
{
	this->id = card->id;
	ui->lblTitle->setText(card->title);

	ui->lblDescription->setText(card->description);

	setStatusIconAndLabel(card->deadline);
	setTimeleft(card->deadline);
	setPriorityIcon(card->priority);

	bool isReminder = dynamic_cast<ReminderCard*>(card) != nullptr;

	setTypeIcon(isReminder);
}

void CellReminder::setStatusIconAndLabel(QDateTime datetime)
{
	if(datetime.isValid())
	{
		ui->wdtDeadline->setVisible(true);
		QString date = datetime.toString("yyyy-MM-dd hh:mm");//TODO:
		ui->lblDeadlineTime->setText(date);
		ui->lblDeadlineTime->setToolTip(date);
	}
	else
	{
		ui->wdtDeadline->setVisible(false);
	}
}

void CellReminder::setTimeleft(QDateTime datetime)
{
	if(datetime.isValid())
	{
		int days = QDate::currentDate().daysTo(datetime.date());

		if(days >= 0)
		{
			ui->lblTimeleft->setText(QString::number(days) +" "+ tr("day(s)"));
			ui->wdtTimeleft->setVisible(true);
		}
		else
		{
			ui->wdtTimeleft->setVisible(false);
		}
	}
	else
	{
		ui->wdtTimeleft->setVisible(false);
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

	ui->imgType->SetPixmap(QPixmap(path));
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

	ui->imgPriority->SetPixmap(QPixmap(path));
}

