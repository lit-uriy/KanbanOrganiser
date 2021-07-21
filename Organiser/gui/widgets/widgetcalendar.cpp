#include "widgetcalendar.h"
#include "ui_widgetcalendar.h"

#include <QLabel>
#include <QPushButton>

#include "remindercalendar.h"
#include "cellnotes.h"

WidgetCalendar::WidgetCalendar(QWidget *parent) :
    WidgetTab(QSize(300,600),parent),
    size(QSize(300,600)),
	ui(new Ui::WidgetCalendar)
{
	ui->setupUi(this);
	connect(ui->wdtReminders,&WidgetReminders::reminderAdded,this,&WidgetCalendar::OnReminderAdded);

}

WidgetCalendar::~WidgetCalendar()
{
	delete ui;
}


Reminders* WidgetCalendar::GetReminders()
{
	return ui->wdtReminders->GetReminders();
}

void WidgetCalendar::SetAppData(AppData* appData)
{
	this->appData = appData;
	ui->wdtReminders->SetAppData(appData);
    calendar.SetAppData(appData);
    updateReminders();

	QDate date = ui->calendarWidget->selectedDate();
	on_calendarWidget_currentPageChanged(date.year(),date.month());
}

void WidgetCalendar::updateReminders()
{
    //appData->reminders = ui->wdtReminders->GetReminders();
	ui->wdtReminders->SetAppData(appData);
	ui->wdtReminders->UpdateData(ui->calendarWidget->selectedDate());
}

void WidgetCalendar::on_calendarWidget_currentPageChanged(int year, int month)
{
    QList<CalendarDay> calendarDays = calendar.GetCalendarDaysForMonth(QDate(year,month,1));
	ui->calendarWidget->SetCalendarDays(calendarDays);
}

void WidgetCalendar::on_calendarWidget_selectionChanged()
{
	updateReminders();
}

void WidgetCalendar::OnReminderAdded()
{
	updateReminders();
	emit reminderAdded();
}
