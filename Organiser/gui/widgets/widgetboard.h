#ifndef WIDGETBOARD_H
#define WIDGETBOARD_H

#include <QWidget>


namespace Ui {
class WidgetBoard;
}

class WidgetBoard : public QWidget
{
		Q_OBJECT

	public:
		explicit WidgetBoard(QWidget *parent = nullptr);
		~WidgetBoard();

		class Board GetBoard();
		void SetBoard(class Board board);

	private:
		Ui::WidgetBoard *ui;

		QList<class WidgetNotes*> columns;
		void updateListView(Board board);
		void clearColumns();
		void addColumnToListView(class BoardColumn column,int id);
		void updateColumnIds();
	private slots:
		void DeleteColumn(int id);

		void on_btnAddColumn_clicked();

};

#endif // WIDGETBOARD_H
