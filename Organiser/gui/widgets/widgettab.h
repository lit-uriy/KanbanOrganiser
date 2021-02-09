#ifndef WIDGETTAB_H
#define WIDGETTAB_H

#include <QWidget>

class WidgetTab : public QWidget
{
		Q_OBJECT
	public:
		explicit WidgetTab(QSize size, QWidget *parent = nullptr);

		QSize GetSize();
	private:
		QSize size;
	signals:

};

#endif // WIDGETTAB_H
