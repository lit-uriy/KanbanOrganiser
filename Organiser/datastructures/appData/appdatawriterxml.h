#ifndef APPDATAWRITERXML_H
#define APPDATAWRITERXML_H

#include "appdata.h"
#include <QDomDocument>


class AppDataWriterXml
{
	public:
		AppDataWriterXml();


		QDomElement Save(AppData appData, QDomDocument document);
		AppData Load(QDomElement root);


		QString GetRootElementName();
		bool IsValid();


		bool WriteToFile(AppData appData,QString path);
		AppData ReadFromFile(QString path);

};

#endif // APPDATAWRITERXML_H
