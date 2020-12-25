#include "noteswriterxml.h"
#include "datastructures/card/cardwriterxml.h"

NotesWriterXml::NotesWriterXml()
{

}

QDomElement NotesWriterXml::Save(Notes notes, QDomDocument document)
{
	QDomElement root = document.createElement(GetRootElementName());

	CardWriterXml cardWriter;

	for(int i=0; i < notes.GetCardsCount();i++)
	{
		Card card = notes.GetCardAt(i);
		QDomElement elementCard = cardWriter.Save(card,document);
		root.appendChild(elementCard);
	}

	document.appendChild(root);

	return root;
}

QString NotesWriterXml::GetRootElementName()
{
	return "Notes";
}

Notes NotesWriterXml::Load(QDomElement root)
{
	Notes notes;

	CardWriterXml cardWriter;
	for(QDomElement elementCard = root.firstChildElement(cardWriter.GetRootElementName());!elementCard.isNull();elementCard = elementCard.nextSiblingElement("Card"))
	{
		Card card = cardWriter.Load(elementCard);

		if(!card.IsNull())
		{
			notes.AddCard(card);
		}
	}

	return notes;
}
