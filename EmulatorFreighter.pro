QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console no_keywords

LIBS += -L C:\Users\akeit\AppData\Local\Programs\Python\Python310\libs -lpython310

INCLUDEPATH += C:\Users\akeit\AppData\Local\Programs\Python\Python310\include

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    functions.h \
    mainwindow.h \
    quickScanner.h \
    structures.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    C:\EmulatorFreighter\Build\debug\scrapeIGDB.py


RC_ICONS = myappico.ico
