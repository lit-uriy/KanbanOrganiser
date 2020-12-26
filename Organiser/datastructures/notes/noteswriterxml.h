#ifndef NOTESWRITERXML_H
#define NOTESWRITERXML_H

#include "notes.h"

#include <QDomDocument>

class NotesWriterXml
{
    public:
        NotesWriterXml();

        QDomElement Save(Notes notes, QDomDocument document);
        QString GetRootElementName();

        Notes Load(QDomElement root);
};

#endif // NOTESWRITERXML_H
