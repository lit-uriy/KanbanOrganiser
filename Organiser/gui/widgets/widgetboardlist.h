#ifndef WIDGETBOARDLIST_H
#define WIDGETBOARDLIST_H

#include <QWidget>

#include "datastructures/board/board.h"

namespace Ui {
class WidgetBoardList;
}

class WidgetBoardList : public QWidget
{
		Q_OBJECT

	public:
		explicit WidgetBoardList(QWidget *parent = nullptr);
		~WidgetBoardList();

		void SetBoardList(QList<Board> boards);
		QList<Board> GetBoardList();
	private:
		Ui::WidgetBoardList *ui;

		int oldIndex = -1;
		QList<Board> boards;

		void addBoard();
		void refreshCombobox();

	private slots:
		void on_btnAddBoard_clicked();

		void on_cbxBoards_currentIndexChanged(int index);
};

#endif // WIDGETBOARDLIST_H
