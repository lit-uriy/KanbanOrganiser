#include "reminderswritterxml.h"

#include "datastructures/reminders/remindercardwritterxml.h"

RemindersWritterXml::RemindersWritterXml()
{

}

QDomElement RemindersWritterXml::Save(Reminders reminders, QDomDocument document)
{
    QDomElement root = document.createElement(GetRootElementName());

    ReminderCardWritterXml cardWriter;

    for(int i=0; i < reminders.GetCardsCount();i++)
    {
        ReminderCard* card = reminders.GetCardAt(i);
        QDomElement elementCard = cardWriter.Save(card,document);
        root.appendChild(elementCard);
    }

    document.appendChild(root);

    return root;
}

QString RemindersWritterXml::GetRootElementName()
{
    return "Reminder";
}

Reminders RemindersWritterXml::Load(QDomElement root)
{
    Reminders reminders;

    ReminderCardWritterXml cardWriter;
    for(QDomElement elementCard = root.firstChildElement(cardWriter.GetRootElementName());!elementCard.isNull();elementCard = elementCard.nextSiblingElement("ReminderCard"))
    {
        ReminderCard* card = cardWriter.Load(elementCard);

        if(!card->IsNull())
        {
            reminders.AddCard(card);
        }
    }

    return reminders;
}
