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
		explicit CellNotes(Card* card, int id, QWidget *parent = nullptr);
		~CellNotes();

		void UpdateCard(Card* card);
		int GetId();

		Card GetCard();

		void SetDatesVisibility(bool visible);
	protected:

		void paintEvent(QPaintEvent *) override;
		void mousePressEvent(QMouseEvent *event) override;
		void mouseMoveEvent(QMouseEvent *event) override;
		void mouseReleaseEvent(QMouseEvent *event) override;


		QPoint dragStartPosition;
	private:
		Ui::CellNotes *ui;

		int id = -1;
		Card* card = nullptr;

		void setWidgetData(Card* card);

		void setStartStatusIconAndLabel(QDateTime startDate);
		void setFinishedStatusIconAndLabel(Card::Status status, QDateTime finishedDate);
		void setStatusIcon(Card::Status status);

		void setPriorityIcon(Card::Priority priority);
	signals:
		void CardMoved(CellNotes* cellNote);
		void CardMovedSuccess(CellNotes* cellNote, bool success);

		void CardDelete(CellNotes* cellNote);
		void CardAdd(CellNotes* cellNote);

};

#endif // CELLNOTES_H
