#ifndef TST_CARD_H
#define TST_CARD_H

#include <QtTest>

class TestCard : public QObject
{
		Q_OBJECT

	public:
		TestCard();
		~TestCard();

	private slots:
		void test_cardCreation();
		void test_compare();
		void test_EncodeDecode();

};

#endif // TST_CARD_H
