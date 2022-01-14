#-------------------------------------------------
#
# Project created by QtCreator 2021-12-12T23:45:02
#
#-------------------------------------------------

QT       += core gui
QT       += sql widgets
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BioDBSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        addcreature.cpp \
        adddistr.cpp \
        basicchange.cpp \
        basicquery.cpp \
        browser.cpp \
        connectionwidget.cpp \
        login.cpp \
        main.cpp \
        registerdialog.cpp \
        showbarchart.cpp

HEADERS += \
        addcreature.h \
        adddistr.h \
        basicchange.h \
        basicquery.h \
        browser.h \
        connectionwidget.h \
        login.h \
        registerdialog.h \
        showbarchart.h

FORMS += \
        addcreature.ui \
        adddistr.ui \
        basicchange.ui \
        basicquery.ui \
        browserwidget.ui \
        login.ui \
        registerdialog.ui \
        showbarchart.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
