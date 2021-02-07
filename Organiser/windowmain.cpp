#include "windowmain.h"
#include "ui_windowmain.h"

#include <QCloseEvent>
#include <QTimer>

#include "datastructures/appData/appdata.h"
#include "datastructures/appData/appdatawriterxml.h"

WindowMain::WindowMain(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::WindowMain)
{
	ui->setupUi(this);
	loadAppDataFromFile();

	showTrayIcon();
	connect(ui->wdtNotes,&WidgetNotes::SaveRequest,this,&WindowMain::saveAppData);

	tempLoad();

	QTimer::singleShot(1000,this,[this](){
		//TODO:Change to launcher screen
		minimizeToTray();
	});
}

void WindowMain::tempLoad()
{

	AppData appData;
	appData.notes = ui->wdtNotes->GetNotes();

	appData.boards = ui->wdtBoard->GetBoardList();
	ui->wdtCalendar->SetAppData(appData);
	ui->wdtCalendar->SetWeeklyCards(QDate::currentDate());


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

	AppDataWriterXml writer;
	QString exePath = QCoreApplication::applicationDirPath();
	writer.WriteToFile(appData,exePath + "/calendar.xml");
}

#include <QDebug>

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
