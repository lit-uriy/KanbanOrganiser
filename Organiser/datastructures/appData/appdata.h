#ifndef APPDATA_H
#define APPDATA_H


#include "datastructures/notes/notes.h"
#include "datastructures/board/board.h"

class AppData
{
	public:
		AppData();

		bool IsValid();

		Notes notes;
		QList<Board> boards;
};

#endif // APPDATA_H
