#ifndef BOARDCOLUMNWRITERXML_H
#define BOARDCOLUMNWRITERXML_H

#include <QDomDocument>

class BoardColumnWriterXml
{
	public:
		BoardColumnWriterXml();
		QString GetRootElementName();

		QDomElement Save(class BoardColumn column, QDomDocument document);
		class BoardColumn Load(QDomElement root);
	private:
};

#endif // BOARDCOLUMNWRITERXML_H
