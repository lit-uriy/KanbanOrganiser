#include "popupmanager.h"
#include "gui/dialogs/dialogpopup.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QSound>

PopupManager::PopupManager(QObject *parent) : QObject(parent)
{
	initTimer();
}

void PopupManager::initTimer()
{
	connect(&timer,&QTimer::timeout,this,&PopupManager::OnTimer);
	setTimerInterval();
	timer.start();
}

void PopupManager::setTimerInterval()
{
	int seconds = QTime::currentTime().second();
	int secondsLeft = 60-seconds;
	timer.setInterval(secondsLeft*1000);
}

void PopupManager::UpdateAppData(AppData appData)
{
	this->appData = appData;
}

void PopupManager::ForcePopups()
{
	checkForReminders();
}

void PopupManager::OnTimer()
{
	setTimerInterval();
	checkForReminders();
}

void PopupManager::checkForReminders()
{
	QList<Card*> cards = calendar.GetCardsForDeadline(QDateTime::currentDateTime(),appData);

	bool newCardShown = false;
	for(int i=0; i < cards.size();i++)
	{
		ReminderCard* card = new ReminderCard(cards[i]);
		if(!isCardVisible(card))
		{
			showPopup(card);
			newCardShown = true;
		}
		delete card;
	}

	if(newCardShown)
	{
		playSound();
	}
}

void PopupManager::playSound()
{
	QSound::play(":/sounds/resources/sounds/popup2.wav");
}

bool PopupManager::isCardVisible(ReminderCard* card)
{
	for(int i=0; i < dialogs.size();i++)
	{
		if(card->id == dialogs.at(i)->GetCardId())
		{
			return true;
		}
	}

	return false;
}

void PopupManager::showPopup(ReminderCard* card)
{
	qDebug() << "showPopup";
	DialogPopup* popup = new DialogPopup(card,dynamic_cast<QWidget*>(parent()));
	connect(popup,&DialogPopup::closed,this,&PopupManager::OnClose);
	connect(popup,&DialogPopup::markAsFinished,this,&PopupManager::OnMarkAsFinished);
	connect(popup,&DialogPopup::postpone,this,&PopupManager::OnPostpone);
	dialogs.append(popup);

	popup->show();
	moveVisiblePopups();
}

void PopupManager::moveVisiblePopups()
{
	if(dialogs.size() == maxPopups+1)
	{
		DialogPopup* popup = dialogs[0];
		popup->close();
	}

	for(int i=0; i < dialogs.size();i++)
	{
		DialogPopup* popup = dialogs[i];
		QPoint position = calculatePopupPosition(popup,dialogs.size()-(i));
		popup->move(position);
	}
}


QPoint PopupManager::calculatePopupPosition(DialogPopup* popup,int index)
{
	QDesktopWidget *desktop = QApplication::desktop();
	QRect rec = desktop->availableGeometry();

	const int offset = 8;
	int x = rec.width() - (popup->size().width() + offset);
	int y = rec.height() - ((index)*(popup->size().height() + offset));

	return QPoint(x,y);
}


void PopupManager::OnClose(DialogPopup* popup)
{
	if(dialogs.removeOne(popup))
	{

	}

	delete popup;

	moveVisiblePopups();
}

void PopupManager::OnMarkAsFinished(DialogPopup* popup)
{
	const unsigned long long id = popup->GetCardId();
	emit CardStatusSetToFinished(id);
}

void PopupManager::OnPostpone(DialogPopup* popup,int minutes)
{
	const unsigned long long id = popup->GetCardId();

	emit PostponeCard(id,minutes);
}
