#ifndef BOARDWRITERXML_H
#define BOARDWRITERXML_H

#include "board.h"
#include <QDomDocument>

class BoardWriterXml
{
	public:
		BoardWriterXml();

        QDomElement Save(Board* board, QDomDocument document);
		QString GetRootElementName();

		Board Load(QDomElement root);
};

#endif // BOARDWRITERXML_H
