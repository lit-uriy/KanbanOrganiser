#ifndef WIDGETNOTES_H
#define WIDGETNOTES_H

#include <QWidget>

#include "datastructures/notes/notes.h"

namespace Ui {
class WidgetNotes;
}

class WidgetNotes : public QWidget
{
		Q_OBJECT

	public:
		explicit WidgetNotes(QWidget *parent = nullptr);
		~WidgetNotes();

		Notes GetNotes();
		void SetNotes(Notes notes);

	private slots:
		void on_btnAddNote_clicked();

		void on_twdNotes_customContextMenuRequested(const QPoint &pos);

		void on_actionEditCard_triggered();

		void on_actionDeleteCard_triggered();

		void on_twdNotes_cellDoubleClicked(int row, int column);

	private:
		Ui::WidgetNotes *ui;

		Notes notes;

		void updateListView();
		void addCardToListView(class Card card,int id);

		void replaceSelectedCard(Card card);

		int getSelectedCardID();
		class CellNotes* getSelectedCell();
		int getSelectedCellIndex();

	signals:
		void SaveRequest();
};


#endif // WIDGETNOTES_H
