QT += core gui webview

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


LIBS += -L C:\Users\akeit\AppData\Local\Programs\Python\Python310\libs -lpython310

#LIBS += .\Python310\libs -lpython310

#INCLUDEPATH += \Python310\include

INCLUDEPATH += C:\Users\akeit\AppData\Local\Programs\Python\Python310\include


#copydata.commands = $(COPY_DIR) $$PWD/scrapeIGDB.py $$OUT_PWD
#first.depends = $(first) copydata
#export(first.depends)
#export(copydata.commands)
#QMAKE_EXTRA_TARGETS += first copydata



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settings.cpp \
    #scrapeIGDB.c \

HEADERS += \
    EmulatorFreighter.h \
    mainwindow.h \
    settings.h \

FORMS += \
    mainwindow.ui \
    settings.ui \

DISTFILES += \
    C:\EmulatorFreighter\scrapeIGDB.py \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
