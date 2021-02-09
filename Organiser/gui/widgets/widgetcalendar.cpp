#include "widgetcalendar.h"
#include "ui_widgetcalendar.h"

#include <QLabel>
#include <QPushButton>

#include "cellnotes.h"

WidgetCalendar::WidgetCalendar(QWidget *parent) :
	WidgetTab(size,parent),
	ui(new Ui::WidgetCalendar)
{
	ui->setupUi(this);
	setHeaderLayoutWeekly(QDate::currentDate());
	currentDate = QDate::currentDate();
}

WidgetCalendar::~WidgetCalendar()
{
	delete ui;
}

void WidgetCalendar::SetAppData(AppData appData)
{
	this->appData = appData;
}

void WidgetCalendar::setHeaderLayoutWeekly(QDate date)
{
	QGridLayout* gridLayout;

	if(ui->wdtHeader->layout() != nullptr)
	{
		gridLayout = (QGridLayout*)ui->wdtHeader->layout();
	}
	else
	{
		gridLayout = new QGridLayout;
	}

	QLayoutItem* item;
	while ( ( item = gridLayout->takeAt( 0 ) ) != NULL )
	{
		delete item->widget();
		delete item;
	}


	QString dayNames[7] = {tr("Monday"),tr("Tuesday"),tr("Wednesday"),tr("Thursday"),tr("Friday"),tr("Saturday"),tr("Sunday")};

	//addWidget(*Widget, row, column, rowspan, colspan)
	QPushButton* buttonPrevious = new QPushButton("<<");
	connect(buttonPrevious,&QPushButton::clicked,this,&WidgetCalendar::onPreviousClicked);

	gridLayout->addWidget(buttonPrevious,0,0,2,1);
	for(int i=0; i < 7;i++)
	{
		gridLayout->addWidget(new QLabel(dayNames[i]),0,i+1,1,1);
		gridLayout->addWidget(new QLabel(date.addDays(i).toString("dd-MM-yyyy")),1,i+1,1,1);
	}


	QPushButton* buttonNext = new QPushButton(">>");
	connect(buttonNext,&QPushButton::clicked,this,&WidgetCalendar::onNextClicked);
	gridLayout->addWidget(buttonNext,0,8,2,1);

	setGridColumnWidths(gridLayout);
	ui->wdtHeader->setLayout(gridLayout);
}

void WidgetCalendar::onPreviousClicked()
{

	currentDate = currentDate.addDays(-7);
	SetWeeklyCards(currentDate);

}

void WidgetCalendar::onNextClicked()
{
	currentDate = currentDate.addDays(7);
	SetWeeklyCards(currentDate);
}

void WidgetCalendar::SetWeeklyCards(QDate date)
{
	currentDate = date;
	QList<Card> cards = calendar.GetCardsForWeek(date,appData);


	int dayNumber = date.dayOfWeek()-1;

	QDate weekStartDay = date.addDays(-dayNumber);

	QGridLayout* gridLayout;

	if(ui->wdtContent->layout() != nullptr)
	{
		gridLayout = (QGridLayout*)ui->wdtContent->layout();
	}
	else
	{
		gridLayout = new QGridLayout;
	}

	gridLayout->setMargin(0);
	QLayoutItem* item;
	while ( ( item = gridLayout->takeAt( 0 ) ) != NULL )
	{
		delete item->widget();
		delete item;
	}

	setGridColumnWidths(gridLayout);

	for(int i=0; i < cards.size();i++)
	{
		addCellWeekly(gridLayout,cards.at(i),weekStartDay,i);
	}
	ui->wdtContent->setLayout(gridLayout);

	setHeaderLayoutWeekly(date);
}

void WidgetCalendar::setGridColumnWidths(QGridLayout* gridLayout)
{
	for(int i=0; i < 9;i++)
	{
		if(i==0 | i == 8)
		{
			gridLayout->setColumnMinimumWidth(i,20);
		}
		else
		{
			gridLayout->setColumnMinimumWidth(i,100);
		}
	}
}

void WidgetCalendar::addCellWeekly(QGridLayout* gridLayout, Card card, QDate startDate, int row)
{
	QDate aStart = card.startDate.date();
	QDate aDeadline = card.deadline.date();

	if(aStart < startDate)
	{
		aStart = startDate.addDays(-1);
	}

	if(aDeadline > startDate.addDays(7))
	{
		aDeadline = startDate.addDays(7);
	}

	int start = 1+startDate.daysTo(aStart);
	int length = 1+aStart.daysTo(aDeadline);


	//addWidget(*Widget, row, column, rowspan, colspan)
	CellNotes* cell = new CellNotes(card,row,this);
	cell->setFixedHeight(50);
	cell->SetDatesVisibility(false);
	gridLayout->addWidget(cell,row,start,1,length);

}
