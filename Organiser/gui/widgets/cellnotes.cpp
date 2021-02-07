#include "cellnotes.h"
#include "ui_cellnotes.h"

#include <QIcon>

#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

#include <QStyle>
#include <QStyleOption>
#include <QPainter>

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

Card CellNotes::GetCard()
{
	return card;
}

void CellNotes::SetDatesVisibility(bool visible)
{
	ui->lblStartTime->setVisible(visible);
	ui->lblFinishedTime->setVisible(visible);
}

void CellNotes::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CellNotes::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);

	setProperty("pressed", true);
	this->style()->polish(this);

	if (event->button() == Qt::LeftButton)
	{
		//dragStartPosition = event->pos();
	}
}

void CellNotes::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);

	this->setProperty("pressed", false);
	this->style()->polish(this);
}

void CellNotes::mouseMoveEvent(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);

	if (!(event->buttons() & Qt::LeftButton))
	{
		return;
	}

	if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance())
	{
		return;
	}


	QDrag *drag = new QDrag(this);
	QMimeData *mimeData = new QMimeData;

	QByteArray dat = card.Encode();
	mimeData->setData("organiser/card", dat);
	drag->setMimeData(mimeData);

	//emit CardDelete(this);

	//emit CardMoved(this);

	Qt::DropAction dropAction = drag->exec(Qt::MoveAction);


	setProperty("pressed", false);
	this->style()->polish(this);

	if(dropAction == Qt::DropAction::MoveAction)
	{
		emit CardMovedSuccess(this,true);
	}
	else
	{
		emit CardMovedSuccess(this,false);
	}

}

void CellNotes::setWidgetData(Card card)
{
	ui->lblTitle->setText(card.title);

	ui->lblDescription->setText(card.description);

	setStartStatusIconAndLabel(card.startDate);
	setFinishedStatusIconAndLabel(card.status,card.GetFinishingDate());

	setPriorityIcon(card.priority);
}

void CellNotes::setStartStatusIconAndLabel(QDateTime startDate)
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

void CellNotes::setFinishedStatusIconAndLabel(Card::Status status, QDateTime finishedDate)
{
	if(finishedDate.isValid())
	{
		ui->wdtFinishedTime->setVisible(true);
		QString date = finishedDate.toString("yyyy-MM-dd hh:mm");//TODO:
		ui->lblFinishedTime->setText(date);
		ui->lblFinishedTime->setToolTip(date);
		setStatusIcon(status);
	}
	else
	{
		ui->wdtFinishedTime->setVisible(false);
	}
}

void CellNotes::setStatusIcon(Card::Status status)
{
	QString path = "";

	switch(status)
	{
		case Card::Status::Started:
			path = ":/icons/resources/icons/edit.png";//TODO:
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
