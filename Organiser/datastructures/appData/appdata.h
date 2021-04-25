#ifndef APPDATA_H
#define APPDATA_H


#include "datastructures/notes/notes.h"
#include "datastructures/board/boards.h"
#include "datastructures/reminders/reminders.h"

class AppData
{
	public:
		AppData();

		bool IsValid();

		Notes notes;
        Boards boards;
		Reminders reminders;

		const Card* FindCard(unsigned long long id);

        void MarkCardAsShown(unsigned long long id);
		void PostponeCard(unsigned long long id,int timeInMinutes);
	private:
		Card* findCard(unsigned long long id);
};

#endif // APPDATA_H
