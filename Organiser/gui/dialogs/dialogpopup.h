#ifndef DIALOGPOPUP_H
#define DIALOGPOPUP_H

#include <QDialog>

namespace Ui {
class DialogPopup;
}

class DialogPopup : public QDialog
{
		Q_OBJECT

	public:
		explicit DialogPopup(class ReminderCard* card, QWidget *parent = nullptr);
		~DialogPopup();

		unsigned long long GetCardId();
	protected:
		void closeEvent(QCloseEvent* event) override;
	private slots:
		void on_btnMarkAsFinished_clicked();

		void on_btnPostpone_clicked();

	private:
		Ui::DialogPopup *ui;

	signals:
		void closed(DialogPopup* popup);
		void markAsFinished(DialogPopup* popup);
		void postpone(DialogPopup* popup, int minutes);
};

#endif // DIALOGPOPUP_H
