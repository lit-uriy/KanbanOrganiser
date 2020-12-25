#include "cardwriterxml.h"

#include "card.h"

const QString CardWriterXml::dateTimeFormat = "yyyy-MM-dd hh:mm:ss";

CardWriterXml::CardWriterXml()
{

}

QDomElement CardWriterXml::Save(Card card, QDomDocument document)
{
	QDomElement root = document.createElement(GetRootElementName());

	root.setAttribute("title", card.title);
	root.setAttribute("description", card.description);
	root.setAttribute("creationDate", card.creationDate.toString(dateTimeFormat));

	root.setAttribute("finishedDate", card.finishedDate.toString(dateTimeFormat));

	root.setAttribute("priority", (int)card.priority);
	root.setAttribute("status", (int)card.status);

	document.appendChild(root);

	return root;
}

QString CardWriterXml::GetRootElementName()
{
	return "Card";
}

Card CardWriterXml::Load(QDomElement root)
{
	Card card;
	card.title = root.attribute("title");
	card.description = root.attribute("description");

	card.creationDate = QDateTime::fromString(root.attribute("creationDate"),dateTimeFormat);
	card.finishedDate = QDateTime::fromString(root.attribute("finishedDate"),dateTimeFormat);

	card.priority = (Card::Priority)root.attribute("priority").toInt();
	card.status = (Card::Status)root.attribute("status").toInt();

	return card;
}
