#ifndef NOTESTABLEWIDGET_H
#define NOTESTABLEWIDGET_H

#include <QTableWidget>
#include "datastructures/card/card.h"

class NotesTableWidget : public QTableWidget
{
		Q_OBJECT

	public:
		NotesTableWidget(QWidget *parent = nullptr);

		void dragEnterEvent(QDragEnterEvent * event) override;
		void dragLeaveEvent(QDragLeaveEvent *event) override;
		void dragMoveEvent(QDragMoveEvent *event) override;
		void dropEvent(QDropEvent *event) override;

	protected:
		void paintEvent(QPaintEvent *event) override;

	private:

		int dropPosition = -1;
		void drawDropIndicator();
		int getDropPositionY();

		int getDropPosition(QDropEvent *event);

	signals:
		void CardDropped(Card* card,int index);
};

#endif // NOTESTABLEWIDGET_H
