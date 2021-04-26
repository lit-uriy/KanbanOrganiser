#ifndef DIALOGCOLUMNEDIT_H
#define DIALOGCOLUMNEDIT_H

#include <QDialog>

namespace Ui {
class DialogColumnEdit;
}

class DialogColumnEdit : public QDialog
{
		Q_OBJECT

	public:
        explicit DialogColumnEdit(QString title, QString text, QWidget *parent = nullptr);
		~DialogColumnEdit();

		QString GetTitle();
	private slots:
		void on_btnAccept_clicked();

		void on_btnCancel_clicked();

	private:
		Ui::DialogColumnEdit *ui;

};

#endif // DIALOGCOLUMNEDIT_H
