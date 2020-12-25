#include "test_noteswriterxml.h"

#include "datastructures/card/card.h"
#include "datastructures/card/cardwriterxml.h"
#include "datastructures/notes/notes.h"
#include "datastructures/notes/noteswriterxml.h"
#include "exceptions/generalexception.h"


test_noteswriterxml::test_noteswriterxml()
{

}

test_noteswriterxml::~test_noteswriterxml()
{

}

void test_noteswriterxml::writeNotesToXml()
{
	QString title = "titleText";
	QString description  = "descriptionText";
	QDateTime creationDate = QDateTime(QDate(2020,1,1),QTime(10,10));

	Notes notes;
	Card card(title,description,creationDate);
	notes.AddCard(card);

	NotesWriterXml writer;
	QDomDocument document;
	QDomElement elementNotes = writer.Save(notes,document);

	notes = writer.Load(elementNotes);

	Card cardLoaded = notes.GetCardAt(0);

	QVERIFY(card == cardLoaded);
}

QTEST_APPLESS_MAIN(test_noteswriterxml)

