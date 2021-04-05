#ifndef POPUPMANAGER_H
#define POPUPMANAGER_H

#include <QObject>
#include <QTimer>
#include <QSoundEffect>

#include "datastructures/appData/appdata.h"
#include "datastructures/calendar/calendar.h"
#include "datastructures/calendar/postponedcard.h"

class PopupManager : public QObject
{
		Q_OBJECT
	public:
		explicit PopupManager(QObject *parent = nullptr);

		void UpdateAppData(AppData appData);

		void ForcePopups();
	private:

		const int maxPopups = 5;

		AppData appData;
		QTimer timer;

		Calendar calendar;
		QList<class DialogPopup*> dialogs;

		void initTimer();
		void initSound();
		void setTimerInterval();

		void checkForReminders();
		bool isCardVisible(ReminderCard* card);
		void showPopup(class ReminderCard* card);
		void moveVisiblePopups();
		QPoint calculatePopupPosition(DialogPopup* popup,int index);

		void playSound();
	private slots:
		void OnTimer();

		void OnClose(DialogPopup* popup);
		void OnMarkAsFinished(DialogPopup* popup);
		void OnPostpone(DialogPopup* popup,int minutes);

	signals:
		void PostponeCard(unsigned long long id,int minutes);
		void CardStatusSetToFinished(unsigned long long id);
};

#endif // POPUPMANAGER_H
