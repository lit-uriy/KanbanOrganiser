#include "iconlabel.h"

#include <QBitmap>
IconLabel::IconLabel(QWidget* parent) : QLabel(parent)
{

}

QColor IconLabel::GetIconColor()
{
	return color;
}

void IconLabel::SetPixmap(const QPixmap &pixmap)
{
	setPixmap(pixmap);
	updateIconColor();
}
void IconLabel::SetIconColor(QColor color)
{
	this->color = color;
}

void IconLabel::showEvent(QShowEvent *event)
{
	QLabel::showEvent(event);
	updateIconColor();
}

void IconLabel::updateIconColor()
{
	setIconColor(color);
}

void IconLabel::setIconColor(QColor color)
{

	QPixmap pixmapNew = pixmap()->copy();

	QBitmap bitmap = pixmapNew.createMaskFromColor(Qt::transparent,Qt::MaskInColor);

	pixmapNew.fill(color);
	pixmapNew.setMask(bitmap);

	setPixmap(pixmapNew);
}
