#include "windowmain.h"
#include "ui_windowmain.h"

#include <QCloseEvent>
#include <QTimer>
#include <QDesktopWidget>

#include "datastructures/appData/appdata.h"
#include "datastructures/appData/appdatawriterxml.h"

#include <QDebug>
#include <QPropertyAnimation>
#include <QEasingCurve>

#include <QButtonGroup>

WindowMain::WindowMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WindowMain)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);




    startSplashScreen();

    loadAppDataFromFile();

    showTrayIcon();
    connect(ui->wdtNotes,&WidgetNotes::SaveRequest,this,&WindowMain::saveAppData);
    connect(ui->wdtCalendar,&WidgetCalendar::reminderAdded,this,&WindowMain::saveAppData);

    tempLoad();

    connect(&minimizeTimer,&QTimer::timeout,this,[this](){
        minimizeToTray();
    });


    QObject::connect(qApp, &QGuiApplication::applicationStateChanged, this, [=](Qt::ApplicationState state){
		//qDebug() << state;

        if(state == Qt::ApplicationState::ApplicationInactive)
        {
            minimizeTimer.start(100);
            //minimizeToTray();
        }
        else
        {
            minimizeTimer.stop();
        }
    });



	connect(ui->btnCalendar,&QPushButton::clicked,this, [this](){
		onSelectableButtonClicked(ui->btnCalendar);
	});
	connect(ui->btnNotes,&QPushButton::clicked,this, [this](){
		onSelectableButtonClicked(ui->btnNotes);
	});
	connect(ui->btnBoard,&QPushButton::clicked,this, [this](){
		onSelectableButtonClicked(ui->btnBoard);
	});
}

void WindowMain::onSelectableButtonClicked(PushButtonSelectable* button)
{
	ui->btnCalendar->SetSelected(false);
	ui->btnNotes->SetSelected(false);
	ui->btnBoard->SetSelected(false);

	PushButtonSelectable* btn = dynamic_cast<PushButtonSelectable*>(button);
	if(btn != nullptr)
	{
		btn->SetSelected(true);
	}
}
void WindowMain::startSplashScreen()
{
    ui->stackedWidget->setCurrentIndex(0);
    on_tabWidget_currentChanged(0);

    ui->prbLoading->setValue(0);
    ui->prbLoading->setMaximum(100);

    setWindowOpacity(0.0);
    QPropertyAnimation *a1 = new QPropertyAnimation(this, "windowOpacity"); // As top level window, uses this one.
    a1->setDuration(splashDuration);
    a1->setStartValue(0.0);
    a1->setKeyValueAt(0.25,1.0);
    a1->setKeyValueAt(0.75,1.0);
    a1->setEndValue(0.0);
    a1->setEasingCurve(QEasingCurve::Linear);
    a1->start(QPropertyAnimation::DeleteWhenStopped);
    connect(a1,&QPropertyAnimation::finished,this,[this](){
        this->setWindowOpacity(1);
        closeSplashScreen();
    });

    QPropertyAnimation *a2 = new QPropertyAnimation(ui->prbLoading, "value"); // As top level window, uses this one.
    a2->setDuration(splashDuration);
    a2->setStartValue(0.0);
    a2->setKeyValueAt(0.25,0.0);
    a2->setKeyValueAt(0.75,100.0);
    a2->setEndValue(100.0);
    a2->setEasingCurve(QEasingCurve::Linear);
    a2->start(QPropertyAnimation::DeleteWhenStopped);

}

void WindowMain::closeSplashScreen()
{
    minimizeToTray();
    ui->stackedWidget->setCurrentIndex(1);
    on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
}

void WindowMain::tempLoad()
{

    AppData appData;
    appData.notes = ui->wdtNotes->GetNotes();
    appData.boards = ui->wdtBoard->GetBoardList();
	appData.reminders = ui->wdtCalendar->GetReminders();

    ui->wdtCalendar->SetAppData(appData);

}

void WindowMain::loadAppDataFromFile()
{
    AppDataWriterXml writer;
    QString exePath = QCoreApplication::applicationDirPath();
    AppData appData = writer.ReadFromFile(exePath + "/calendar.xml");

    ui->wdtNotes->SetNotes(appData.notes);

    ui->wdtBoard->SetBoardList(appData.boards);
    ui->wdtCalendar->SetAppData(appData);
}

WindowMain::~WindowMain()
{
    saveAppData();
    delete ui;
}

void WindowMain::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void WindowMain::saveAppData()
{
    saveAppDataToFile();
}

void WindowMain::saveAppDataToFile()
{
    AppData appData;
    appData.notes = ui->wdtNotes->GetNotes();

    appData.boards = ui->wdtBoard->GetBoardList();

    appData.reminders = ui->wdtCalendar->GetReminders();
    AppDataWriterXml writer;
    QString exePath = QCoreApplication::applicationDirPath();
    writer.WriteToFile(appData,exePath + "/calendar.xml");
}

void WindowMain::showTrayIcon()
{
    updateTrayIcon();
    updateTrayIconMenu();

    connect(&trayIcon, &QSystemTrayIcon::activated, this, &WindowMain::onTrayClick);
    trayIcon.show();
}

void WindowMain::onTrayClick(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::ActivationReason::DoubleClick:
            if(minimizedToTray)
            {
                maximizeFromTray();
            }
            else
            {
                minimizeToTray();
            }
            break;
        default:
            break;
    }

}

void WindowMain::updateTrayIconMenu()
{
    menu.clear();

    if(minimizedToTray)
    {
        menu.addAction(ui->actionTrayShow);
    }
    else
    {
        menu.addAction(ui->actionTrayMinimize);
    }

    menu.addSeparator();
    menu.addAction(ui->actionTrayQuit);


    trayIcon.setContextMenu(&menu);
}

void WindowMain::updateTrayIcon()
{
    QIcon icon(":/icons/resources/icons/organiser_icon.png");
    trayIcon.setIcon(icon);
    trayIcon.setToolTip(tr("Featherlight organiser"));
}

void WindowMain::closeEvent(QCloseEvent* event)
{
    if(!minimizedToTray)
    {
        minimizeToTray();
        event->ignore();
    }
    else
    {
        QMainWindow::closeEvent(event);
    }
}


void WindowMain::on_actionTrayShow_triggered()
{
    maximizeFromTray();
}

void WindowMain::maximizeFromTray()
{
    this->show();

    this->activateWindow();
    this->raise();

    minimizedToTray = false;
    updateTrayIconMenu();
}

void WindowMain::on_actionTrayMinimize_triggered()
{
    minimizeToTray();
}

void WindowMain::minimizeToTray()
{
    this->hide();
    minimizedToTray = true;
    updateTrayIconMenu();
}

void WindowMain::on_actionTrayQuit_triggered()
{
    exitApp();
}

void WindowMain::exitApp()
{
    minimizedToTray = true;
    close();
}

#include <QSettings>

void WindowMain::setBootAtStartup(bool enabled)
{
    //TODO: Cos nie dziala
    QSettings bootUpSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

    const QString appName = "Organiser";//TODO:
    if (enabled)
    {
        QString app_path = "\"" + QCoreApplication::applicationFilePath() + "\"";
        bootUpSettings.setValue(appName, app_path);
    }
    else
    {
        bootUpSettings.remove(appName);
    }

}

void WindowMain::on_btnTest1_clicked()
{
    setBootAtStartup(true);
}

void WindowMain::on_btnTest2_clicked()
{
    setBootAtStartup(false);
}

void WindowMain::on_tabWidget_currentChanged(int index)
{
    QSize size;
    if(ui->stackedWidget->currentIndex() == 0)
    {
        size = QSize(300,240);
    }
    else
    {
        switch(index)
        {
            case 0:
                size = ui->wdtCalendar->GetSize();
                break;
            case 1:
                size = ui->wdtNotes->GetSize();
                break;
            case 2:
                size = ui->wdtBoard->GetSize();
                break;
        }
    }


    setScreenGeometry(size);
}


void WindowMain::setScreenGeometry(QSize size)
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect rec = desktop->availableGeometry();

    int x = rec.width() - size.width();
    int y = rec.height() - size.height();
    setGeometry(x,y,size.width(),size.height());
    setFixedSize(size);
}

void WindowMain::on_btnNotes_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tabNotes);
}

void WindowMain::on_btnBoard_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tabBoards);
}

void WindowMain::on_btnCalendar_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tabCalendar);
	ui->btnCalendar->SetSelected(true);
}

