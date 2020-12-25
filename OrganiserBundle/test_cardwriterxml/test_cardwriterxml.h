#ifndef TEST_CARDWRITERXML_H
#define TEST_CARDWRITERXML_H

#include <QtTest>

class test_cardwriterxml : public QObject
{
		Q_OBJECT

	public:
		test_cardwriterxml();
		~test_cardwriterxml();

	private slots:
		void writeCardToXml();

};


#endif // TEST_CARDWRITERXML_H
