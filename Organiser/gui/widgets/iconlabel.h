#ifndef ICONLABEL_H
#define ICONLABEL_H

#include <QObject>
#include <QLabel>

class IconLabel : public QLabel
{
		Q_OBJECT
		Q_PROPERTY(QColor iconColor READ GetIconColor WRITE SetIconColor)

	public:
		IconLabel(QWidget* parent);

		QColor GetIconColor();
		void SetIconColor(QColor color);

		void SetPixmap(const QPixmap &pixmap);

	protected:
		virtual void showEvent(QShowEvent *event) override;

	private:
		QColor color;

		void setIconColor(QColor color);

		void updateIconColor();
};

#endif // ICONLABEL_H
