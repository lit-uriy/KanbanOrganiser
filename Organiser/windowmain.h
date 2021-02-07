#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WindowMain; }
QT_END_NAMESPACE

#include <QSystemTrayIcon>
#include <QMenu>

class WindowMain : public QMainWindow
{
		Q_OBJECT

	public:
		WindowMain(QWidget *parent = nullptr);
		~WindowMain();

	protected:

		void showEvent(QShowEvent *event) override;
		void closeEvent(QCloseEvent *event) override;
	private:
		Ui::WindowMain *ui;

		void tempLoad();//TODO:Delete later

		bool minimizedToTray = false;
		QMenu menu;

		QSystemTrayIcon trayIcon;

		void showTrayIcon();
		void updateTrayIconMenu();

		void updateTrayIcon();

		void minimizeToTray();
		void maximizeFromTray();
		void exitApp();

		void saveAppDataToFile();
		void loadAppDataFromFile();

		void setBootAtStartup(bool enabled);

	private slots:
		void saveAppData();
		void onTrayClick(QSystemTrayIcon::ActivationReason reason);

		void on_btnTest1_clicked();

		void on_btnTest2_clicked();

		void on_actionTrayShow_triggered();
		void on_actionTrayMinimize_triggered();
		void on_actionTrayQuit_triggered();
};
#endif // WINDOWMAIN_H
