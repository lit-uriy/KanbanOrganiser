#ifndef APPDATA_H
#define APPDATA_H


#include "datastructures/notes/notes.h"

class AppData
{
	public:
		AppData();

		bool IsValid();

		Notes notes;
};

#endif // APPDATA_H
