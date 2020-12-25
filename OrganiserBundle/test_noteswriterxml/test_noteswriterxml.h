#ifndef TEST_NOTESWRITERXML_H
#define TEST_NOTESWRITERXML_H

#include <QtTest>

class test_noteswriterxml : public QObject
{
		Q_OBJECT

	public:
		test_noteswriterxml();
		~test_noteswriterxml();

	private slots:
		void writeNotesToXml();

};


#endif // TEST_NOTESWRITERXML_H
