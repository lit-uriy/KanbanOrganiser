#include "widgetboard.h"
#include "ui_widgetboard.h"

#include "widgetnotes.h"

#include "datastructures/board/board.h"

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

Board WidgetBoard::GetBoard()
{
	Board board;

	for(int i=0; i < columns.size();i++)
	{
		BoardColumn column = columns[i]->GetColumn();
		board.AddColumn(column);
	}

	return board;
}

void WidgetBoard::SetBoard(Board board)
{
	updateListView(board);
}

void WidgetBoard::updateListView(Board board)
{
	clearColumns();
	for(int i=0; i < board.GetColumnCount();i++)
	{
		BoardColumn column = board.GetColumnAt(i);
		addColumnToListView(column,i);
	}
}

void WidgetBoard::clearColumns()
{
	for(int i=0; i < columns.size();i++)
	{
		ui->wdtColumnList->layout()->removeWidget(columns[i]);
		columns[i]->deleteLater();
	}

	columns.clear();
}

void WidgetBoard::addColumnToListView(BoardColumn column,int id)
{
	WidgetNotes* columnWidget = new WidgetNotes(column,id,this);

	columnWidget->setFixedWidth(200);//TODO:
	ui->wdtColumnList->layout()->addWidget(columnWidget);

	columns.append(columnWidget);
}

void WidgetBoard::on_btnAddColumn_clicked()
{
	BoardColumn column;

	//TODO: SetT
	column.title = "TEst";

	addColumnToListView(column,columns.size());
}
