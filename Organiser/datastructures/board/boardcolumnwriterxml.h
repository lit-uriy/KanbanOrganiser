#ifndef BOARDCOLUMNWRITERXML_H
#define BOARDCOLUMNWRITERXML_H

#include "boardcolumn.h"
#include <QDomDocument>

class BoardColumnWriterXml
{
	public:
		BoardColumnWriterXml();
		QString GetRootElementName();

        QDomElement Save(BoardColumn* column, QDomDocument document);
        BoardColumn* Load(QDomElement root);
	private:
};

#endif // BOARDCOLUMNWRITERXML_H
