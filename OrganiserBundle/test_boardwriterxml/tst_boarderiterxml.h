#ifndef TST_BOARDERITERXML_H
#define TST_BOARDERITERXML_H

#include <QtTest>

// add necessary includes here

#include "datastructures/board/board.h"
#include "datastructures/board/boardwriterxml.h"
#include "exceptions/generalexception.h"

class test_BoardWriterXml : public QObject
{
		Q_OBJECT

	public:
		test_BoardWriterXml();
		~test_BoardWriterXml();

	private slots:
		void writeBoardToXml();

};

#endif // TST_BOARDERITERXML_H
