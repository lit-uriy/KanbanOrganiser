#include "widgetboard.h"
#include "ui_widgetboard.h"

#include "widgetnotes.h"

WidgetBoard::WidgetBoard(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::WidgetBoard)
{
	ui->setupUi(this);
}

WidgetBoard::~WidgetBoard()
{
	delete ui;
}

void WidgetBoard::on_btnAddColumn_clicked()
{
	WidgetNotes* column = new WidgetNotes(this);

	column->SetTitle(tr("Title"));//TODO:
	column->setFixedWidth(200);//TODO:
	ui->wdtColumnList->layout()->addWidget(column);
}
