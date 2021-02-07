#ifndef TST_CALENDAR_H
#define TST_CALENDAR_H

#include <QtTest>
#include "datastructures/appData/appdata.h"

// add necessary includes here

class calendar : public QObject
{
		Q_OBJECT

	public:
		calendar();
		~calendar();

		AppData appData;
		Card card;
		Card card2;
		Card card3;
	private slots:
		void getDayCards();
		void getWeekCards();

};

#endif // TST_CALENDAR_H
