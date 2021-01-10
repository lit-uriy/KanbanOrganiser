#include "boardcolumnwriterxml.h"

#include "datastructures/card/cardwriterxml.h"

BoardColumnWriterXml::BoardColumnWriterXml()
{

}

QDomElement BoardColumnWriterXml::Save(BoardColumn column, QDomDocument document)
{
	QDomElement root = document.createElement(GetRootElementName());

	root.setAttribute("title", column.title);

	CardWriterXml cardWriter;
	for(int i=0; i < column.GetCardsCount();i++)
	{
		Card card = column.GetCardAt(i);
		QDomElement elementCard = cardWriter.Save(card,document);
		root.appendChild(elementCard);
	}

	document.appendChild(root);

	return root;
}

QString BoardColumnWriterXml::GetRootElementName()
{
	return "BoardColumn";
}

BoardColumn BoardColumnWriterXml::Load(QDomElement root)
{
	BoardColumn column;

	column.title = root.attribute("title");

	CardWriterXml cardWriter;
	for(QDomElement elementCard = root.firstChildElement(cardWriter.GetRootElementName());!elementCard.isNull();elementCard = elementCard.nextSiblingElement("Card"))
	{
		Card card = cardWriter.Load(elementCard);

		if(!card.IsNull())
		{
			column.AddCard(card);
		}
	}

	return column;
}
