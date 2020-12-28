#ifndef CELLNOTES_H
#define CELLNOTES_H

#include <QWidget>

#include "datastructures/card/card.h"

namespace Ui {
class CellNotes;
}

class CellNotes : public QWidget
{
		Q_OBJECT

	public:
		explicit CellNotes(Card card, int id, QWidget *parent = nullptr);
		~CellNotes();

		void UpdateCard(Card card);
		int GetId();

	protected:
		void mousePressEvent(QMouseEvent *event) override;
		void mouseMoveEvent(QMouseEvent *event) override;
		QPoint dragStartPosition;
	private:
		Ui::CellNotes *ui;

		int id = -1;
		Card card;

		void setWidgetData(Card card);

		void setStatusIconAndLabel(Card::Status status, QDateTime finishedDate);
		void setStatusIcon(Card::Status status);

		void setPriorityIcon(Card::Priority priority);
	signals:
		void CardMoved(CellNotes* cellNote);
};

#endif // CELLNOTES_H
