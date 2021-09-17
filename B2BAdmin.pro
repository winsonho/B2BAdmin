#-------------------------------------------------
#
# Project created by QtCreator 2019-06-14T11:01:02
#
#-------------------------------------------------
include(QZXing/QZXing.pri)

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = B2BAdmin
TEMPLATE = app

#QMAKE_POST_LINK+="/Users/winsonho/Qt5/5.13.1/clang_64/bin/macdeployqt B2BAdmin.app -dmg"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 sdk_no_version_check

SOURCES += \
    channelprofile.cpp \
    dialogeditjson.cpp \
        main.cpp \
        mainwidget.cpp \
    dbhandler.cpp \
    jsonhandler.cpp \
    newaccountwidget.cpp \
    qrcodewidget.cpp

HEADERS += \
    channelprofile.h \
    dialogeditjson.h \
        mainwidget.h \
    dbhandler.h \
    jsonhandler.h \
    common.h \
    mystylesheet.h \
    newaccountwidget.h \
    qrcodewidget.h \
    version.h

FORMS += \
    channelprofile.ui \
    dialogeditjson.ui \
        mainwidget.ui \
    newaccountwidget.ui \
    qrcodewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
