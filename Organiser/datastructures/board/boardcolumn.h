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

		bool operator==(const BoardColumn &other);
		bool operator!=(const BoardColumn &other);

		QString title = "";

		bool IsNull();
	private:
		bool isEqual(const BoardColumn &other);
};

#endif // BOARDCOLUMN_H
