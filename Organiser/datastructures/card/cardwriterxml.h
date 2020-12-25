#ifndef CARDWRITERXML_H
#define CARDWRITERXML_H

#include <QDomDocument>

class CardWriterXml
{
	public:
		CardWriterXml();
		QString GetRootElementName();

		QDomElement Save(class Card notes, QDomDocument document);
		class Card Load(QDomElement root);
	private:
		static const QString dateTimeFormat;
};

#endif // CARDWRITERXML_H
