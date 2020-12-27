#include "boardwriterxml.h"

#include "boardcolumnwriterxml.h"

BoardWriterXml::BoardWriterXml()
{

}

QDomElement BoardWriterXml::Save(Board board, QDomDocument document)
{
	QDomElement root = document.createElement(GetRootElementName());

	root.setAttribute("title", board.title);

	BoardColumnWriterXml columnWriter;
	for(int i=0; i < board.GetColumnCount();i++)
	{
		BoardColumn column = board.GetColumnAt(i);
		QDomElement elementCard = columnWriter.Save(column,document);
		root.appendChild(elementCard);
	}

	document.appendChild(root);

	return root;
}

QString BoardWriterXml::GetRootElementName()
{
	return "Board";
}

Board BoardWriterXml::Load(QDomElement root)
{
	Board board;
	board.title = root.attribute("title");

	BoardColumnWriterXml columnWriter;
	for(QDomElement elementCard = root.firstChildElement(columnWriter.GetRootElementName());!elementCard.isNull();elementCard = elementCard.nextSiblingElement(columnWriter.GetRootElementName()))
	{
		BoardColumn column = columnWriter.Load(elementCard);

		if(!column.IsNull())
		{
			board.AddColumn(column);
		}
	}

	return board;
}
