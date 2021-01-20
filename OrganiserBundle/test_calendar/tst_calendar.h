#ifndef TST_CALENDAR_H
#define TST_CALENDAR_H

#include <QtTest>

// add necessary includes here

class calendar : public QObject
{
		Q_OBJECT

	public:
		calendar();
		~calendar();

	private slots:
		void getDayCards();
		void getWeekCards();

};

#endif // TST_CALENDAR_H
