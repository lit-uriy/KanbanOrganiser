#include "widgetnotes.h"
#include "ui_widgetnotes.h"

#include "datastructures/card/card.h"
#include "gui/dialogs/dialogcard.h"
#include "cellnotes.h"
#include "gui/dialogs/dialogcolumnedit.h"

#include <QMenu>


WidgetNotes::WidgetNotes(QWidget *parent) :
    WidgetTab(QSize(300,600),parent),
    size(QSize(300,600)),
    ui(new Ui::WidgetNotes)
{
    ui->setupUi(this);
    ui->lblTitle->setText("");

    setAcceptDrops(true);

    connect(ui->twdNotes,&NotesTableWidget::CardDropped,this,&WidgetNotes::OnCardDropped);
}

WidgetNotes::WidgetNotes(BoardColumn* column, int id,QWidget *parent) :
    WidgetTab(QSize(100,100),parent),
    ui(new Ui::WidgetNotes)
{
    ui->setupUi(this);
    SetNotes(column);
    this->title = column->title;
    this->id = id;

    ui->lblTitle->setText(title);

    connect(ui->twdNotes,&NotesTableWidget::CardDropped,this,&WidgetNotes::OnCardDropped);
}


WidgetNotes::~WidgetNotes()
{
    delete ui;
}

QString WidgetNotes::GetTitle()
{
    return title;
}

void WidgetNotes::SetTitle(QString title)
{
    ui->lblTitle->setText(title);
    this->title = title;
}

Notes* WidgetNotes::GetNotes()
{
    return notes;
}

void WidgetNotes::SetColumnEditable(bool editable)
{
    ui->btnColumnOptions->setVisible(editable);
}

void WidgetNotes::SetNotes(Notes* notes)
{
    this->notes = notes;
    updateListView();
}

int WidgetNotes::GetId()
{
    return id;
}

BoardColumn* WidgetNotes::GetColumn()
{
    BoardColumn* column = new BoardColumn();

    column->title = title;

    for(int i=0; i < notes->GetCardsCount();i++)
    {
        Card* card = notes->GetCardAt(i);
        column->AddCard(card);
    }

    return column;
}

void WidgetNotes::SetId(int id)
{
    this->id = id;
}

void WidgetNotes::updateListView()
{
    const int count = notes->GetCardsCount();

    ui->twdNotes->setRowCount(0);

    for(int i=0; i < count;i++)
    {
        Card* card = notes->GetCardAt(i);
        addCardToListView(card,i);
    }
}


void WidgetNotes::addCardToListView(Card* card, int id)
{
    ui->twdNotes->insertRow(0);

    CellNotes* cell = new CellNotes(card,id,ui->twdNotes);
    connect(cell,&CellNotes::CardMovedSuccess,this,&WidgetNotes::OnCardMovedSuccess);
    ui->twdNotes->setCellWidget(0,0,cell);
}

void WidgetNotes::OnCardMovedSuccess(CellNotes* cell,bool success)
{
    if(!internalDrag && success)
    {
        deleteCard(cell->GetId());
    }

    internalDrag = false;
}

void WidgetNotes::OnCardDropped(Card* card, int position)
{
    const int cardIndex = notes->Find(card);

    internalDrag = cardIndex > -1;

    if(internalDrag)
    {
        Card* cardNew = new Card(card);
        delete card;


        if(cardIndex == position)
        {
            return;
        }

        if(cardIndex < position)
        {
            position--;
        }

        deleteCard(cardIndex);
        notes->AddCardAt(position,cardNew);
        updateListView();
    }
    else
    {
        Card* cardNew = new Card(card);
        delete card;

        notes->AddCardAt(position,cardNew);
        updateListView();
    }
}

void WidgetNotes::on_btnAddNote_clicked()
{
    DialogCard dialogCard(this);

    if(dialogCard.exec() == QDialog::Accepted)
    {
        Card* card = dialogCard.GetCard();
        notes->AddCard(card);
        updateListView();

        emit SaveRequest();
    }
}


void WidgetNotes::on_twdNotes_customContextMenuRequested(const QPoint &pos)
{
    QPoint position = ui->twdNotes->mapToGlobal(pos);

    if(ui->twdNotes->itemAt(position) == nullptr)
    {
        //return;
    }

    QMenu menu;

    menu.addAction(ui->actionEditCard);
    menu.addAction(ui->actionDeleteCard);

    menu.exec(position);
}

void WidgetNotes::on_twdNotes_cellDoubleClicked(int row, int column)
{
    on_actionEditCard_triggered();
}

void WidgetNotes::on_actionEditCard_triggered()
{
    int id = getSelectedCardID();

    if(id == -1)
    {
        return;
    }

    DialogCard dialogCard(notes->GetCardAt(id),this);


    if(dialogCard.exec() == QDialog::Accepted)
    {
        Card* card = dialogCard.GetCard();
        notes->ReplaceCard(id,card);
        replaceSelectedCard(card);

        emit SaveRequest();
    }
}

void WidgetNotes::replaceSelectedCard(Card* card)
{
    CellNotes* cell = getSelectedCell();
    cell->UpdateCard(card);
}

int WidgetNotes::getSelectedCardID()
{
    CellNotes* cellNote = getSelectedCell();

    return cellNote->GetId();
}

CellNotes* WidgetNotes::getSelectedCell()
{
    int row = getSelectedCellIndex();

    if(row == -1)
    {
        return nullptr;
    }

    return dynamic_cast<CellNotes*>(ui->twdNotes->cellWidget(row,0));
}

int WidgetNotes::getSelectedCellIndex()
{
    QItemSelectionModel *select = ui->twdNotes->selectionModel();

    QModelIndexList indexlist = select->selectedRows();

    if(indexlist.size() == 0)
    {
        return -1;
    }

    QModelIndex index = indexlist.first();
    int row = index.row();

    return row;
}

void WidgetNotes::on_actionDeleteCard_triggered()
{
    int id = getSelectedCardID();
    deleteCard(id);
}

void WidgetNotes::deleteCard(int id)
{
    if(id == -1)
    {
        return;
    }

    notes->DeleteCard(id);
    updateListView();

    emit SaveRequest();
}

void WidgetNotes::on_btnColumnOptions_clicked()
{
    QMenu menu(this);

    menu.addAction(ui->actionRenameColumn);
    menu.addSeparator();
    menu.addAction(ui->actionDeleteColumn);

    QPoint position = ui->btnColumnOptions->mapToGlobal(QPoint(0-ui->btnColumnOptions->width(),ui->btnColumnOptions->height()));
    menu.exec(position);
}

void WidgetNotes::on_actionRenameColumn_triggered()
{
    DialogColumnEdit dialogColumnEdit(tr("Rename column"),title);

    if(dialogColumnEdit.exec() == QDialog::Accepted)
    {
        SetTitle(dialogColumnEdit.GetTitle());
    }
}

void WidgetNotes::on_actionDeleteColumn_triggered()
{
    emit DeleteRequest(id);
}
