#ifndef WIDGETBOARDLIST_H
#define WIDGETBOARDLIST_H

#include <QWidget>
#include "widgettab.h"

#include "datastructures/board/boards.h"

namespace Ui {
class WidgetBoardList;
}

class WidgetBoardList : public WidgetTab
{
    Q_OBJECT

    public:
        explicit WidgetBoardList(QWidget *parent = nullptr);
        ~WidgetBoardList();

        void SetBoardList(Boards* boards);
        Boards* GetBoardList();
    private:
        Ui::WidgetBoardList *ui;
        constexpr static QSize size = QSize(910,600);

        int oldIndex = -1;
        Boards* boards;

        void addBoard();
        void refreshCombobox();

    private slots:
        void on_btnAddBoard_clicked();

        void on_cbxBoards_currentIndexChanged(int index);
        void on_btnEditBoard_clicked();
        void on_btnDeleteBoard_clicked();
    signals:
        void SaveRequest();
};

#endif // WIDGETBOARDLIST_H
