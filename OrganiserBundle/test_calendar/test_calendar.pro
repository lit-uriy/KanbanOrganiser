QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SRC_PATH = ../../Organiser
INCLUDEPATH += $$SRC_PATH
DEPENDPATH += $$SRC_PATH

SOURCES += tst_calendar.cpp \
     $$SRC_PATH/datastructures/calendar/calendar.cpp \
     $$SRC_PATH/datastructures/card/card.cpp \
     $$SRC_PATH/datastructures/reminders/remindercard.cpp \
     $$SRC_PATH/datastructures/reminders/reminders.cpp \
     $$SRC_PATH/datastructures/board/board.cpp \
     $$SRC_PATH/datastructures/board/boards.cpp \
     $$SRC_PATH/datastructures/board/boardcolumn.cpp  \
     $$SRC_PATH/datastructures/notes/notes.cpp \
     $$SRC_PATH/datastructures/appdata/appdata.cpp

HEADERS += \
    tst_calendar.h

