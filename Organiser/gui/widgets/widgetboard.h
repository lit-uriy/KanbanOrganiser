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

	private slots:
		void on_btnAddColumn_clicked();

	private:
		Ui::WidgetBoard *ui;
};

#endif // WIDGETBOARD_H
