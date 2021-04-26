#include "widgetboardlist.h"
#include "ui_widgetboardlist.h"

#include "gui/dialogs/dialogcolumnedit.h"

WidgetBoardList::WidgetBoardList(QWidget *parent) :
	WidgetTab(size,parent),
	ui(new Ui::WidgetBoardList)
{
	ui->setupUi(this);

    connect(ui->wdtBoard,&WidgetBoard::SaveRequest,this,&WidgetBoardList::SaveRequest);
}

WidgetBoardList::~WidgetBoardList()
{
	delete ui;
}

void WidgetBoardList::SetBoardList(Boards* boards)
{
	this->boards = boards;
	refreshCombobox();
}

Boards* WidgetBoardList::GetBoardList()
{
    return boards;
}

void WidgetBoardList::refreshCombobox()
{

	ui->cbxBoards->blockSignals(true);

	ui->cbxBoards->clear();

    for(int i=0; i < boards->GetSize();i++)
	{
        QString title = boards->GetBoard(i)->title;

		if(title.isNull() || title.isEmpty())
		{
			title = tr("Board") + " " + QString::number(i+1);
		}

		ui->cbxBoards->addItem(title);
	}

	ui->cbxBoards->blockSignals(false);

    if(boards->GetSize() > 0)
	{
        ui->wdtBoard->SetBoard(boards->GetBoard(0));
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

    DialogColumnEdit dialogColumnEdit(tr("Create board"),tr("New board"));

    if(dialogColumnEdit.exec() == QDialog::Accepted)
    {
        board.title = dialogColumnEdit.GetTitle();
        boards->AddBoard(board);
        if(oldIndex > -1)
        {
            boards->boards.replace(oldIndex,ui->wdtBoard->GetBoard());
        }

        refreshCombobox();
        oldIndex = -1;
        ui->cbxBoards->setCurrentIndex(boards->GetSize()-1);
        emit SaveRequest();
    }
}

void WidgetBoardList::on_cbxBoards_currentIndexChanged(int index)
{
	if(oldIndex > -1)
	{
        boards->boards.replace(oldIndex,ui->wdtBoard->GetBoard());
	}

    ui->wdtBoard->SetBoard(boards->GetBoard(index));

	oldIndex = index;
}

void WidgetBoardList::on_btnEditBoard_clicked()
{
    int index = ui->cbxBoards->currentIndex();
    QString title = boards->boards[index].title;

    DialogColumnEdit dialogColumnEdit(tr("Rename board"),title);

    if(dialogColumnEdit.exec() == QDialog::Accepted)
    {
        boards->boards[index].title = dialogColumnEdit.GetTitle();
        refreshCombobox();
        oldIndex = -1;
        ui->cbxBoards->setCurrentIndex(index);
        emit SaveRequest();
    }

}

void WidgetBoardList::on_btnDeleteBoard_clicked()
{
    int index = ui->cbxBoards->currentIndex();
    if(boards->DeleteBoard(index))
    {
        refreshCombobox();
        ui->cbxBoards->setCurrentIndex(0);
        emit SaveRequest();
    }
}
