#include "cardwriterxml.h"

#include "card.h"

const QString CardWriterXml::dateTimeFormat = "yyyy-MM-dd hh:mm:ss";

CardWriterXml::CardWriterXml()
{

}

QDomElement CardWriterXml::Save(Card* card, QDomDocument document)
{
	QDomElement root = document.createElement(GetRootElementName());

	root.setAttribute("id", card->id);

	root.setAttribute("title", card->title);
	root.setAttribute("description", card->description);

	root.setAttribute("creationDate", card->creationDate.toString(dateTimeFormat));
	root.setAttribute("finishedDate", card->finishedDate.toString(dateTimeFormat));

	root.setAttribute("startDate", card->startDate.toString(dateTimeFormat));
	root.setAttribute("deadline", card->deadline.toString(dateTimeFormat));

	root.setAttribute("priority", (int)card->priority);
	root.setAttribute("status", (int)card->status);

	root.setAttribute("postponedDeadline", card->postponedDeadline.toString(dateTimeFormat));

	document.appendChild(root);

	return root;
}

QString CardWriterXml::GetRootElementName()
{
	return "Card";
}

Card* CardWriterXml::Load(QDomElement root)
{
	Card* card = new Card();
	card->id = root.attribute("id").toULongLong();
	card->title = root.attribute("title");
	card->description = root.attribute("description");

	card->creationDate = QDateTime::fromString(root.attribute("creationDate"),dateTimeFormat);
	card->finishedDate = QDateTime::fromString(root.attribute("finishedDate"),dateTimeFormat);

	card->startDate = QDateTime::fromString(root.attribute("startDate"),dateTimeFormat);
	card->deadline = QDateTime::fromString(root.attribute("deadline"),dateTimeFormat);

	card->priority = (Card::Priority)root.attribute("priority").toInt();
	card->status = (Card::Status)root.attribute("status").toInt();

	card->postponedDeadline = QDateTime::fromString(root.attribute("postponedDeadline"),dateTimeFormat);

	return card;
}
