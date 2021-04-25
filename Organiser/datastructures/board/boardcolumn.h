#ifndef BOARDCOLUMN_H
#define BOARDCOLUMN_H

#include <QString>
#include "datastructures/notes/notes.h"
#include "datastructures/card/card.h"

class BoardColumn : public Notes
{
	public:
		BoardColumn();
		BoardColumn(QString title);

		QString title = "";

		bool IsNull();
        bool isEqual(const BoardColumn* other);
    private:
};

#endif // BOARDCOLUMN_H
