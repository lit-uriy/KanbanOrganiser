#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WindowMain; }
QT_END_NAMESPACE

#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimer>
#include "gui/widgets/pushbuttonselectable.h"
#include "gui/popup/popupmanager.h"

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
        PopupManager* popupManager = nullptr;
        AppData appData;

		const int splashDuration = 1000;
		void startSplashScreen();
		void closeSplashScreen();

		QTimer minimizeTimer;

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
        void injectAppData();

		void setBootAtStartup(bool enabled);

		void setScreenGeometry(QSize size);
	private slots:
		void onCardStatusSetToFinished(unsigned long long id);
		void onPostponeCard(unsigned long long id,int minutes);
		void onSelectableButtonClicked(PushButtonSelectable* button);

		void saveAppData();
		void onTrayClick(QSystemTrayIcon::ActivationReason reason);

		void on_btnTest1_clicked();

		void on_btnTest2_clicked();

		void on_actionTrayShow_triggered();
		void on_actionTrayMinimize_triggered();
		void on_actionTrayQuit_triggered();
		void on_tabWidget_currentChanged(int index);
		void on_btnNotes_clicked();
		void on_btnBoard_clicked();
		void on_btnCalendar_clicked();
};
#endif // WINDOWMAIN_H
