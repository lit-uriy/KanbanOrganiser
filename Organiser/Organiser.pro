

QT += core gui network xml

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Organiser
TEMPLATE = app

VERSION = 0.1.0.0
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datastructures/Notes/notes.cpp \
    datastructures/appData/appdata.cpp \
    datastructures/appData/appdatawriterxml.cpp \
    datastructures/board/board.cpp \
    datastructures/board/boardcolumn.cpp \
    datastructures/board/boardcolumnwriterxml.cpp \
    datastructures/board/boardwriterxml.cpp \
    datastructures/calendar/calendar.cpp \
    datastructures/card/card.cpp \
    datastructures/card/cardwriterxml.cpp \
    datastructures/reminders/remindercard.cpp \
    datastructures/reminders/remindercardwritterxml.cpp \
    datastructures/reminders/reminders.cpp \
    datastructures/reminders/reminderswritterxml.cpp \
    gui/dialogs/dialogcard.cpp \
    gui/dialogs/dialogcolumnedit.cpp \
    gui/widgets/notestablewidget.cpp \
    gui/widgets/widgetboard.cpp \
    gui/widgets/widgetboardlist.cpp \
    gui/widgets/widgetcalendar.cpp \
    gui/widgets/widgetreminders.cpp \
    gui/widgets/widgettab.cpp \
    main.cpp \
    datastructures/notes/noteswriterxml.cpp \
    gui/widgets/cellnotes.cpp \
    gui/widgets/widgetnotes.cpp \
    windowmain.cpp

HEADERS += \
    datastructures/appData/appdata.h \
    datastructures/ appData/appdatawriterxml.h \
    datastructures/appData/appdatawriterxml.h \
    datastructures/board/board.h \
    datastructures/board/boardcolumn.h \
    datastructures/board/boardcolumnwriterxml.h \
    datastructures/board/boardwriterxml.h \
    datastructures/calendar/calendar.h \
    datastructures/card/cardwriterxml.h \
    datastructures/reminders/remindercard.h \
    datastructures/reminders/remindercardwritterxml.h \
    datastructures/reminders/reminders.h \
    datastructures/reminders/reminderswritterxml.h \
    exceptions/generalexception.h \
    datastructures/notes/notes.h \
    datastructures/card/card.h \
    gui/dialogs/dialogcard.h \
    gui/dialogs/dialogcolumnedit.h \
    gui/widgets/notestablewidget.h \
    gui/widgets/widgetboard.h \
    datastructures/notes/noteswriterxml.h \
    gui/widgets/cellnotes.h \
    gui/widgets/widgetboardlist.h \
    gui/widgets/widgetcalendar.h \
    gui/widgets/widgetnotes.h \
    gui/widgets/widgetreminders.h \
    gui/widgets/widgettab.h \
    windowmain.h

FORMS += \
    gui/dialogs/dialogcard.ui \
    gui/dialogs/dialogcolumnedit.ui \
    gui/widgets/cellnotes.ui \
    gui/widgets/widgetboard.ui \
    gui/widgets/widgetboardlist.ui \
    gui/widgets/widgetcalendar.ui \
    gui/widgets/widgetnotes.ui \
    gui/widgets/widgetreminders.ui \
    windowmain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
