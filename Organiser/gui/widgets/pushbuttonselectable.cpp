#include "pushbuttonselectable.h"

#include <QBitmap>
#include <QMouseEvent>

PushButtonSelectable::PushButtonSelectable(QWidget* parent) : QPushButton(parent)
{
	updateIconColor();
}

QColor PushButtonSelectable::GetNormalColor()
{
	return normalColor;
}
void PushButtonSelectable::SetNormalColor(QColor color)
{
	normalColor = color;
}

QColor PushButtonSelectable::GetSelectedColor()
{
	return selectedColor;
}
void PushButtonSelectable::SetSelectedColor(QColor color)
{
	selectedColor = color;
}

void PushButtonSelectable::SetSelected(bool selected)
{
	setChecked(selected);
	updateIconColor();
}

void PushButtonSelectable::mousePressEvent(QMouseEvent *e)
{
	QPushButton::mousePressEvent(e);
	pressed = true;
	updateIconColor();
}

void PushButtonSelectable::mouseReleaseEvent(QMouseEvent *e)
{
	QPushButton::mouseReleaseEvent(e);
	pressed = false;
	updateIconColor();
}


void PushButtonSelectable::mouseMoveEvent(QMouseEvent *event)
{
	if(pressed)
	{
		//TODO:
		if(0 < event->x() && this->width() > event->x() &&
			0 < event->y() && this->height() > event->y())
		{
			if(!dragWithinBound)
			{
				dragWithinBound = true;
				updateIconColor();
			}
		}
		else
		{
			if(dragWithinBound)
			{
				dragWithinBound = false;
				updateIconColor();
			}
		}
	}

	QPushButton::mouseMoveEvent(event);
}

#include <QDebug>

void PushButtonSelectable::updateIconColor()
{

	if((isChecked() && !pressed) || (pressed && dragWithinBound))
	{
		qDebug() << "selectedCol";
		setIconColor(selectedColor);
	}
	else
	{
		qDebug() << "normalColor";
		setIconColor(normalColor);
	}
}


void PushButtonSelectable::setIconColor(QColor color)
{
	if(icon().availableSizes().size() > 0)
	{
		QSize size = icon().availableSizes().at(0);

		QPixmap pixmap = icon().pixmap(size);

		QBitmap bitmap = pixmap.createMaskFromColor(Qt::transparent,Qt::MaskInColor);

		pixmap.fill(color);
		pixmap.setMask(bitmap);

		QIcon iconNew(pixmap);
		setIcon(iconNew);
	}

}
