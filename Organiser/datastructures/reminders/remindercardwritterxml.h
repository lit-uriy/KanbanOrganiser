#ifndef REMINDERWRITTERXML_H
#define REMINDERWRITTERXML_H

#include <QDomDocument>

class ReminderCardWritterXml
{
	public:
		ReminderCardWritterXml();

		QString GetRootElementName();

		QDomElement Save(class ReminderCard* notes, QDomDocument document);
		class ReminderCard* Load(QDomElement root);
	private:
		static const QString dateTimeFormat;
};

#endif // REMINDERWRITTERXML_H
