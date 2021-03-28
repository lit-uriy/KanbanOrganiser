#ifndef ICONLABEL_H
#define ICONLABEL_H

#include <QObject>
#include <QLabel>

class IconLabel : public QLabel
{
		Q_OBJECT
		Q_PROPERTY(QColor iconColor READ GetIconColor WRITE SetIconColor)

		QColor GetIconColor();
		void SetIconColor(QColor color);
	public:
		IconLabel(QWidget* parent);

	protected:
		virtual void showEvent(QShowEvent *event) override;
	private:
		QColor color;

		void updateIconColor();

		void setIconColor(QColor color);
};

#endif // ICONLABEL_H
