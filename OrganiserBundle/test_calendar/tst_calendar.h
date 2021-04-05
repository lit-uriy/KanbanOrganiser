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
		Card* card = nullptr;
		Card* card2 = nullptr;
		Card* card3 = nullptr;
	private slots:
		void getDayCards();
		void getWeekCards();

		void getCardsForDeadline();
};

#endif // TST_CALENDAR_H
