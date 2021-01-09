#include "widgetboardlist.h"
#include "ui_widgetboardlist.h"

WidgetBoardList::WidgetBoardList(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::WidgetBoardList)
{
	ui->setupUi(this);
}

WidgetBoardList::~WidgetBoardList()
{
	delete ui;
}

void WidgetBoardList::SetBoardList(QList<Board> boards)
{
	this->boards = boards;
	refreshCombobox();
}

QList<Board> WidgetBoardList::GetBoardList()
{
	if(ui->cbxBoards->currentIndex() > -1)
	{
		boards.replace(ui->cbxBoards->currentIndex(),ui->wdtBoard->GetBoard());
	}

	return boards;
}

void WidgetBoardList::refreshCombobox()
{

	ui->cbxBoards->blockSignals(true);

	ui->cbxBoards->clear();

	for(int i=0; i < boards.size();i++)
	{
		QString title = boards.at(i).title;

		if(title.isNull() || title.isEmpty())
		{
			title = tr("Board") + " " + QString::number(i+1);
		}

		ui->cbxBoards->addItem(title);
	}

	ui->cbxBoards->blockSignals(false);

	if(boards.size() > 0)
	{
		ui->wdtBoard->SetBoard(boards.at(0));
		ui->wdtBoard->setVisible(true);
	}
	else
	{
		ui->wdtBoard->setVisible(false);
	}
}

void WidgetBoardList::on_btnAddBoard_clicked()
{
	addBoard();
}

void WidgetBoardList::addBoard()
{
	Board board;
	board.title = "Test";//TODO:

	boards.append(board);

	if(oldIndex > -1)
	{
		boards.replace(oldIndex,ui->wdtBoard->GetBoard());
	}

	refreshCombobox();

	ui->cbxBoards->setCurrentIndex(boards.size()-1);
}

void WidgetBoardList::on_cbxBoards_currentIndexChanged(int index)
{
	if(oldIndex > -1)
	{
		boards.replace(oldIndex,ui->wdtBoard->GetBoard());
	}

	ui->wdtBoard->SetBoard(boards.at(index));

	oldIndex = index;
}
