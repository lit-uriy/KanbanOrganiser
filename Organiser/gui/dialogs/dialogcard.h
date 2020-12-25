#ifndef DIALOGCARD_H
#define DIALOGCARD_H

#include <QDialog>

#include "datastructures/card/card.h"

namespace Ui {
class DialogCard;
}

class DialogCard : public QDialog
{
		Q_OBJECT

	public:
		explicit DialogCard(QWidget *parent = nullptr);
		explicit DialogCard(Card card, QWidget *parent = nullptr);
		~DialogCard();

		class Card GetCard();

	private slots:
		void on_btnAccept_clicked();

		void on_btnCancel_clicked();

	private:
		Ui::DialogCard *ui;

		Card card;

		void setWidgetData(Card card);
		void changeAcceptButtonToApply();
};

#endif // DIALOGCARD_H
