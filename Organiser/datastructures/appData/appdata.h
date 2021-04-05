#ifndef APPDATA_H
#define APPDATA_H


#include "datastructures/notes/notes.h"
#include "datastructures/board/board.h"
#include "datastructures/reminders/reminders.h"

class AppData
{
	public:
		AppData();

		bool IsValid();

		Notes notes;
		QList<Board> boards;
		Reminders reminders;

		const Card* FindCard(unsigned long long id);

		void SetCardStatusToFinished(unsigned long long id);
		void PostponeCard(unsigned long long id,int timeInMinutes);
	private:
		Card* findCard(unsigned long long id);
};

#endif // APPDATA_H
