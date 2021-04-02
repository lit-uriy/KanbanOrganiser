#ifndef WIDGETNOTES_H
#define WIDGETNOTES_H

#include <QWidget>

#include "datastructures/notes/notes.h"
#include "datastructures/board/boardcolumn.h"
#include "widgettab.h"

namespace Ui {
class WidgetNotes;
}

class WidgetNotes : public WidgetTab
{
		Q_OBJECT

	public:
		explicit WidgetNotes(QWidget *parent = nullptr);
		explicit WidgetNotes(BoardColumn column, int id,QWidget *parent = nullptr);
		~WidgetNotes();

		Notes GetNotes();
		void SetNotes(Notes notes);

		QString GetTitle();
		void SetTitle(QString title);

		int GetId();

		BoardColumn GetColumn();

		void SetId(int id);

	private:
		Ui::WidgetNotes *ui;
		constexpr static QSize size = QSize(300,600);

		bool internalDrag = false;

		int id = -1;
		Notes notes;
		QString title;

		void updateListView();
		void addCardToListView(class Card* card,int id);

		void replaceSelectedCard(Card* card);

		int getSelectedCardID();
		class CellNotes* getSelectedCell();
		int getSelectedCellIndex();
		void deleteCard(int id);

	private slots:
		void OnCardMovedSuccess(CellNotes* cell,bool success);
		void OnCardDropped(Card* card, int position);


		void on_btnAddNote_clicked();

		void on_twdNotes_customContextMenuRequested(const QPoint &pos);

		void on_actionEditCard_triggered();

		void on_actionDeleteCard_triggered();

		void on_twdNotes_cellDoubleClicked(int row, int column);

		void on_btnColumnOptions_clicked();

		void on_actionRenameColumn_triggered();

		void on_actionDeleteColumn_triggered();



	signals:
		void SaveRequest();
		void DeleteRequest(int id);
};


#endif // WIDGETNOTES_H
