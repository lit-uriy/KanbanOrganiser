#include "appdatawriterxml.h"

#include <QFile>
#include <QTextStream>

#include "datastructures/notes/noteswriterxml.h"
#include "datastructures/board/boardwriterxml.h"

AppDataWriterXml::AppDataWriterXml()
{

}

QDomElement AppDataWriterXml::Save(AppData appData, QDomDocument document)
{
	QDomElement root = document.createElement(GetRootElementName());

	NotesWriterXml notesWriterXml;
	root.appendChild(notesWriterXml.Save(appData.notes,document));


	BoardWriterXml boardWriterXml;

	QDomElement boardList = document.createElement("BoardList");

	for(int i=0; i < appData.boards.size();i++)
	{
		boardList.appendChild(boardWriterXml.Save(appData.boards.at(i),document));
	}

	root.appendChild(boardList);

	document.appendChild(root);

	return root;
}

QString AppDataWriterXml::GetRootElementName()
{
	return "AppData";
}

AppData AppDataWriterXml::Load(QDomElement root)
{
	AppData appData;

	NotesWriterXml notesWriterXml;
	QDomElement elementNotes = root.firstChildElement(notesWriterXml.GetRootElementName());
	Notes notes = notesWriterXml.Load(elementNotes);
	appData.notes = notes;

	BoardWriterXml boardWriterXml;

	QDomElement elementBoardList = root.firstChildElement("BoardList");

	for(QDomElement elementBoard = elementBoardList.firstChildElement(boardWriterXml.GetRootElementName());!elementBoard.isNull();elementBoard = elementBoard.nextSiblingElement(boardWriterXml.GetRootElementName()))
	{
		Board board = boardWriterXml.Load(elementBoard);
		appData.boards.append(board);
	}

	return appData;
}

bool AppDataWriterXml::WriteToFile(AppData appData,QString path)
{

	QDomDocument document("");
	document.appendChild(Save(appData,document));

	QString xml = document.toString();

	QFile file(path);

	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return false;
	}

	QTextStream stream(&file);
	stream << document.toString();
	file.close();

	return true;
}

AppData AppDataWriterXml::ReadFromFile(QString path)
{
	AppData appData;

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return appData;
	}

	QDomDocument document;
	if (!document.setContent(&file))
	{
		file.close();
		return appData;
	}
	file.close();

	QDomElement root = document.firstChildElement("AppData");
	appData = Load(root);

	return appData;
}
