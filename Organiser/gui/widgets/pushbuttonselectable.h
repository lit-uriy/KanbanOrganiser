#ifndef PUSHBUTTONSELECTABLE_H
#define PUSHBUTTONSELECTABLE_H

#include <QPushButton>

class PushButtonSelectable : public QPushButton
{
	public:
		PushButtonSelectable(QWidget* parent=nullptr);

		void SetSelected(bool selected);

	protected:
		void mousePressEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;

		void mouseMoveEvent(QMouseEvent *event) override;
	private:
		bool pressed = false;
		bool dragWithinBound = true;

		QColor normalColor = QColor(0xFA,0xFA,0xFA);
		QColor selectedColor = QColor(0x22,0x22,0x22);

		void updateIconColor();
		void setIconColor(QColor color);

};

#endif // PUSHBUTTONSELECTABLE_H
