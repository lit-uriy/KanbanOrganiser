#include "notestablewidget.h"

#include <QDragMoveEvent>
#include <QMimeData>
#include <QDropEvent>

#include <QPainter>
#include <QDebug>
#include <QCoreApplication>
#include <QScrollBar>

NotesTableWidget::NotesTableWidget(QWidget *parent) : QTableWidget(parent)
{

}


void NotesTableWidget::paintEvent(QPaintEvent* event)
{
	QTableWidget::paintEvent(event);
	drawDropIndicator();
}

/*
void NotesTableWidget::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
	QTableWidget::selectionChanged(selected,deselected);

	QModelIndexList list = selected.indexes();

	QModelIndex index = list.at(0);
	int row = index.row();

	setCellSelected(row);
}

#include "cellnotes.h"

void NotesTableWidget::setCellSelected(int index)
{
	CellNotes* cell = dynamic_cast<CellNotes*>(cellWidget(index,0));

	//cell->SetSelected(true);
}
*/
void NotesTableWidget::drawDropIndicator()
{
	if(dropPosition == -1)
	{
		return;
	}

	QPainter paint(viewport());

	QPen pen(dropLineColor);
	pen.setWidth(3);
	paint.setPen(pen);

	int dropY = getDropPositionY() - verticalScrollBar()->value();
	paint.drawLine(0, dropY, width(), dropY);
}

int NotesTableWidget::getDropPositionY()
{
	int Y = 0;
	for(int i=0; i < dropPosition;i++)
	{
		Y += rowHeight(i);
	}

	return Y;
}

void NotesTableWidget::dragEnterEvent(QDragEnterEvent * event)
{
	if(event->mimeData()->hasFormat("organiser/card"))
	{
		event->acceptProposedAction();
	}
}

void NotesTableWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
	dropPosition = -1;
	viewport()->update();
}


void NotesTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
	if(event->mimeData()->hasFormat("organiser/card"))
	{
		event->accept();
		dropPosition = getDropPosition(event);
		viewport()->update();
	}
	else
	{
		dropPosition = -1;
		viewport()->update();
	}

}

void NotesTableWidget::dropEvent(QDropEvent *event)
{
    const QMimeData *md = event->mimeData();

    QByteArray ba = md->data("organiser/card");

    if(md->hasFormat("organiser/card"))
	{
        Card* card = new Card(ba);
		event->acceptProposedAction();

		emit CardDropped(card, rowCount()-getDropPosition(event));
	}

	dropPosition = -1;
	viewport()->update();
	QCoreApplication::processEvents(QEventLoop::AllEvents,1000);
}

int NotesTableWidget::getDropPosition(QDropEvent *event)
{
	const int eventY = event->pos().y();

	const int rows = rowCount();

	for(int i=0; i < rows;i++)
	{
		const int height = rowHeight(i);
		const int start = rowViewportPosition(i) - height/2;
		const int end = start + height;


		if(eventY < end && start < eventY )
		{
			return i;
		}
	}

	return rows;
}
