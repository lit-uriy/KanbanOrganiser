#ifndef REMINDERSWRITTERXML_H
#define REMINDERSWRITTERXML_H


#include "reminders.h"

#include <QDomDocument>

class RemindersWritterXml
{
	public:
		RemindersWritterXml();

		QDomElement Save(Reminders notes, QDomDocument document);
		QString GetRootElementName();

		Reminders Load(QDomElement root);
};

#endif // REMINDERSWRITTERXML_H
