#include "tst_boarderiterxml.h"

test_BoardWriterXml::test_BoardWriterXml()
{

}

test_BoardWriterXml::~test_BoardWriterXml()
{

}

void test_BoardWriterXml::writeBoardToXml()
{
	QString title = "titleText";
	QString description  = "descriptionText";
	QDateTime creationDate = QDateTime(QDate(2020,1,1),QTime(10,10));

	Board board;
	QString boardTitle = "TEst";
	board.title = boardTitle;
	BoardColumn column("Column1");

	Card card(title,description,creationDate);
	column.AddCard(card);

	board.AddColumn(column);

	BoardWriterXml writer;
	QDomDocument document;
	QDomElement elementNotes = writer.Save(board,document);

	board = writer.Load(elementNotes);

	BoardColumn columnLoaded = board.GetColumnAt(0);

	QVERIFY(column == columnLoaded);
	QVERIFY(board.title == boardTitle);
}

QTEST_APPLESS_MAIN(test_BoardWriterXml)
