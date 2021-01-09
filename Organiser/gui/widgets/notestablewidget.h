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

	protected slots:
		//void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;

	private:

		int dropPosition = -1;
		void drawDropIndicator();
		int getDropPositionY();

		int getDropPosition(QDropEvent *event);


		void setCellSelected(int index);
	signals:
		void CardDropped(Card* card,int index);
};

#endif // NOTESTABLEWIDGET_H
