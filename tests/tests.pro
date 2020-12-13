QT += testlib
#QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
QT += core gui network widgets

TEMPLATE = app

SRC_PATH = H:/Programowanie/QT/organiser/Organiser
INCLUDEPATH += $$SRC_PATH
DEPENDPATH += $$SRC_PATH


SOURCES += tst_card.cpp \
     $$SRC_PATH/card/card.cpp

HEADERS += \


