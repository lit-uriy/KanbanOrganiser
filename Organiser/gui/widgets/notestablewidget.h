#ifndef NOTESTABLEWIDGET_H
#define NOTESTABLEWIDGET_H

#include <QTableWidget>
#include "datastructures/card/card.h"

class NotesTableWidget : public QTableWidget
{
		Q_OBJECT

		Q_PROPERTY(QColor dropLineColor READ getLineColor WRITE setLineColor DESIGNABLE true)

	public:
		NotesTableWidget(QWidget *parent = nullptr);


		void dragEnterEvent(QDragEnterEvent * event) override;
		void dragLeaveEvent(QDragLeaveEvent *event) override;
		void dragMoveEvent(QDragMoveEvent *event) override;
		void dropEvent(QDropEvent *event) override;

		void setLineColor(QColor color){dropLineColor = color;}
		QColor getLineColor(){return dropLineColor;}
	protected:
		void paintEvent(QPaintEvent *event) override;

	protected slots:
		//void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;

	private:
		QColor dropLineColor;
		int dropPosition = -1;
		void drawDropIndicator();
		int getDropPositionY();

		int getDropPosition(QDropEvent *event);


		void setCellSelected(int index);
	signals:
		void CardDropped(Card* card,int index);
};

#endif // NOTESTABLEWIDGET_H
