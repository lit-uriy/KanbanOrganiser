#include "notestablewidget.h"

#include <QDragMoveEvent>
#include <QMimeData>


NotesTableWidget::NotesTableWidget(QWidget *parent) : QTableWidget(parent)
{

}

void NotesTableWidget::dragEnterEvent(QDragEnterEvent * event)
{
	if(event->mimeData()->hasFormat("organiser/card"))
	{
		event->acceptProposedAction();
	}
}

void NotesTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
	if(event->mimeData()->hasFormat("organiser/card"))
	{
		event->accept();
	}
}

#include <QMimeData>
#include <QDropEvent>

void NotesTableWidget::dropEvent(QDropEvent *event)
{
	if(event->mimeData()->hasFormat("organiser/card"))
	{
		Card* card = new Card(event->mimeData()->data("organiser/card"));
		event->acceptProposedAction();

		emit CardDropped(card, getDropPosition(event));
	}
}

int NotesTableWidget::getDropPosition(QDropEvent *event)
{
	return 0;//TODO:
}
