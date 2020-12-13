/********************************************************************************
** Form generated from reading UI file 'windowmain.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWMAIN_H
#define UI_WINDOWMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowMain
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowMain)
    {
        if (WindowMain->objectName().isEmpty())
            WindowMain->setObjectName(QString::fromUtf8("WindowMain"));
        WindowMain->resize(800, 600);
        centralwidget = new QWidget(WindowMain);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        WindowMain->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowMain);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        WindowMain->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowMain);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        WindowMain->setStatusBar(statusbar);

        retranslateUi(WindowMain);

        QMetaObject::connectSlotsByName(WindowMain);
    } // setupUi

    void retranslateUi(QMainWindow *WindowMain)
    {
        WindowMain->setWindowTitle(QCoreApplication::translate("WindowMain", "WindowMain", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowMain: public Ui_WindowMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWMAIN_H
