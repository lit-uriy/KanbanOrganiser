TEMPLATE = subdirs

SUBDIRS += \
    ../Organiser \
    test_board \
    test_boardwriterxml \
    test_calendar \
    test_card \
    test_notes \
    test_notes \
    test_appdatawriterxml \
    test_cardwriterxml \
    test_noteswriterxml \
    test_reminders

CONFIG += qt \
    qt

QT += widgets
