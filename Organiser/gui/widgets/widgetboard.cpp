#include "widgetboard.h"
#include "ui_widgetboard.h"

#include "widgetnotes.h"
#include "datastructures/board/board.h"
#include "gui/dialogs/dialogcolumnedit.h"

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

	board.title = title;
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
	title = board.title;
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

	columnWidget->setFixedWidth(250);//TODO:
	ui->wdtColumnList->layout()->addWidget(columnWidget);

	connect(columnWidget,&WidgetNotes::DeleteRequest,this,&WidgetBoard::DeleteColumn);
	columns.append(columnWidget);
}

void WidgetBoard::DeleteColumn(int id)
{
	if(id > -1 && id < columns.size())
	{
		ui->wdtColumnList->layout()->removeWidget(columns[id]);
		columns[id]->deleteLater();
		columns.removeAt(id);

		updateColumnIds();
	}
}

void WidgetBoard::updateColumnIds()
{
	for(int i=0; i < columns.size();i++)
	{
		columns[i]->SetId(i);
	}
}

void WidgetBoard::on_btnAddColumn_clicked()
{
	DialogColumnEdit dialogColumnEdit(tr("New column"));

	if(dialogColumnEdit.exec() == QDialog::Accepted)
	{
		BoardColumn column;
		column.title = dialogColumnEdit.GetTitle();
		addColumnToListView(column,columns.size());
	}
}
