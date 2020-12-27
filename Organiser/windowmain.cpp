#include "windowmain.h"
#include "ui_windowmain.h"

#include "datastructures/appData/appdata.h"
#include "datastructures/appData/appdatawriterxml.h"

WindowMain::WindowMain(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::WindowMain)
{
	ui->setupUi(this);
	loadAppDataFromFile();

	connect(ui->wdtNotes,&WidgetNotes::SaveRequest,this,&WindowMain::saveAppData);
}

WindowMain::~WindowMain()
{
	saveAppData();
	delete ui;
}

void WindowMain::saveAppData()
{
	saveAppDataToFile();
}

void WindowMain::saveAppDataToFile()
{
	AppData appData;
	appData.notes = ui->wdtNotes->GetNotes();

	appData.board= ui->wdtBoard->GetBoard();

	AppDataWriterXml writer;
	writer.WriteToFile(appData,"C:/Users/Hato/Desktop/test.xml");
}

void WindowMain::loadAppDataFromFile()
{
	AppDataWriterXml writer;
	AppData appData = writer.ReadFromFile("C:/Users/Hato/Desktop/test.xml");

	ui->wdtNotes->SetNotes(appData.notes);
	ui->wdtBoard->SetBoard(appData.board);
}


void WindowMain::on_btnTest1_clicked()
{

}

void WindowMain::on_btnTest2_clicked()
{

}
