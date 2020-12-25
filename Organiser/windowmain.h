#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WindowMain; }
QT_END_NAMESPACE

class WindowMain : public QMainWindow
{
		Q_OBJECT

	public:
		WindowMain(QWidget *parent = nullptr);
		~WindowMain();

	private slots:
		void saveAppData();

		void on_btnTest1_clicked();

		void on_btnTest2_clicked();

	private:
		Ui::WindowMain *ui;

		void saveAppDataToFile();
		void loadAppDataFromFile();
};
#endif // WINDOWMAIN_H
