QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
QT += core network widgets

TEMPLATE = app

SRC_PATH = ../../Organiser
INCLUDEPATH += $$SRC_PATH
DEPENDPATH += $$SRC_PATH

SOURCES +=  tst_notes.cpp \
     $$SRC_PATH/datastructures/card/card.cpp \
     $$SRC_PATH/datastructures/notes/notes.cpp

HEADERS += \
    test_notes.h
