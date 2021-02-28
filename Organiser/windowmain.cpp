#include "windowmain.h"
#include "ui_windowmain.h"

#include <QCloseEvent>
#include <QTimer>
#include <QDesktopWidget>

#include "datastructures/appData/appdata.h"
#include "datastructures/appData/appdatawriterxml.h"

#include <QDebug>

WindowMain::WindowMain(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::WindowMain)
{
	ui->setupUi(this);
	ui->stackedWidget->setCurrentIndex(0);

	setWindowFlags(Qt::FramelessWindowHint);
	loadAppDataFromFile();

	showTrayIcon();
	connect(ui->wdtNotes,&WidgetNotes::SaveRequest,this,&WindowMain::saveAppData);
	connect(ui->wdtReminders,&WidgetReminders::SaveRequest,this,&WindowMain::saveAppData);

	tempLoad();

	connect(&minimizeTimer,&QTimer::timeout,this,[this](){
		minimizeToTray();
	});

	QTimer::singleShot(3000,this,[this](){
		//TODO:Change to launcher screen
		minimizeToTray();
		ui->stackedWidget->setCurrentIndex(1);
		on_tabReminders_currentChanged(ui->tabReminders->currentIndex());
	});

	QObject::connect(qApp, &QGuiApplication::applicationStateChanged, this, [=](Qt::ApplicationState state){
		qDebug() << state;

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

	on_tabReminders_currentChanged(0);
}

void WindowMain::tempLoad()
{

	AppData appData;
	appData.notes = ui->wdtNotes->GetNotes();

	appData.boards = ui->wdtBoard->GetBoardList();
	ui->wdtCalendar->SetAppData(appData);
	ui->wdtCalendar->SetWeeklyCards(QDate::currentDate());


	appData.reminders = ui->wdtReminders->GetReminders();
	ui->wdtReminders->SetAppData(appData);
	ui->wdtReminders->UpdateData(QDate::currentDate());

}

void WindowMain::loadAppDataFromFile()
{
	AppDataWriterXml writer;
	QString exePath = QCoreApplication::applicationDirPath();
	AppData appData = writer.ReadFromFile(exePath + "/calendar.xml");

	ui->wdtNotes->SetNotes(appData.notes);

	ui->wdtBoard->SetBoardList(appData.boards);
	ui->wdtReminders->SetAppData(appData);
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

	appData.reminders = ui->wdtReminders->GetReminders();
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
	QIcon icon(":/icons/resources/icons/featherlight-icon.png");
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

void WindowMain::on_tabReminders_currentChanged(int index)
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
				size = ui->wdtNotes->GetSize();
				break;
			case 1:
				size = ui->wdtBoard->GetSize();
				break;
			case 2:
				size = ui->wdtCalendar->GetSize();
				break;
			case 3:
				size = ui->wdtReminders->GetSize();
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
