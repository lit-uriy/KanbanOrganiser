#include "cellnotes.h"
#include "ui_cellnotes.h"

#include <QIcon>

CellNotes::CellNotes(Card card, int id, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CellNotes)
{
	ui->setupUi(this);

	this->id = id;
	UpdateCard(card);
}

CellNotes::~CellNotes()
{
	delete ui;
}

void CellNotes::UpdateCard(Card card)
{
	this->card = card;
	setWidgetData(card);
}

int CellNotes::GetId()
{
	return id;
}

void CellNotes::setWidgetData(Card card)
{
	ui->lblTitle->setText(card.title);

	ui->lblDescription->setText(card.description);

	ui->lblStartTime->setText(card.creationDate.toString());

	setStatusIconAndLabel(card.status,card.finishedDate);

	setPriorityIcon(card.priority);
}

void CellNotes::setStatusIconAndLabel(Card::Status status, QDateTime finishedDate)
{
	if(status == Card::Status::Started)
	{
		ui->wdtFinishedTime->setVisible(false);
	}
	else
	{
		ui->wdtFinishedTime->setVisible(true);
		ui->lblFinishedTime->setText(finishedDate.toString());
		setStatusIcon(status);
	}
}

void CellNotes::setStatusIcon(Card::Status status)
{
	QString path = "";

	switch(status)
	{
		case Card::Status::Started:
			break;
		case Card::Status::Finished:
			path = ":/icons/resources/icons/check.png";
			break;
		case Card::Status::Canceled:
			path = ":/icons/resources/icons/close.png";
			break;
	}

	ui->imgFinished->setPixmap(QPixmap(path));
}

void CellNotes::setPriorityIcon(Card::Priority priority)
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
