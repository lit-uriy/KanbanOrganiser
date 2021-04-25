#include "dialogcolumnedit.h"
#include "ui_dialogcolumnedit.h"

DialogColumnEdit::DialogColumnEdit(QString title, QString text, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogColumnEdit)
{
	ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->tedTitle->setText(text);
    setWindowTitle(title);
}

DialogColumnEdit::~DialogColumnEdit()
{
	delete ui;
}

QString DialogColumnEdit::GetTitle()
{
	return ui->tedTitle->text();
}

void DialogColumnEdit::on_btnAccept_clicked()
{
	accept();
}

void DialogColumnEdit::on_btnCancel_clicked()
{
	reject();
}
