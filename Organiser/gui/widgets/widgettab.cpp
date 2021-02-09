#include "widgettab.h"

WidgetTab::WidgetTab(QSize size, QWidget *parent) : QWidget(parent)
{
	this->size = size;
}

QSize WidgetTab::GetSize()
{
	return size;
}
