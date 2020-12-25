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
	private:
		Ui::CellNotes *ui;

		int id = -1;
		Card card;

		void setWidgetData(Card card);

		void setStatusIconAndLabel(Card::Status status, QDateTime finishedDate);
		void setStatusIcon(Card::Status status);

		void setPriorityIcon(Card::Priority priority);
};

#endif // CELLNOTES_H
