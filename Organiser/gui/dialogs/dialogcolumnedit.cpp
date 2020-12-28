#include "dialogcolumnedit.h"
#include "ui_dialogcolumnedit.h"

DialogColumnEdit::DialogColumnEdit(QString title, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogColumnEdit)
{
	ui->setupUi(this);
	ui->tedTitle->setText(title);
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
