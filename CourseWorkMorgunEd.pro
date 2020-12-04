#-------------------------------------------------
#
# Project created by QtCreator 2018-12-20T14:49:54
#
#-------------------------------------------------

QT       += core gui multimedia

win32
{
    RC_FILE = winicon.rc
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseWorkMorgunEd
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
        main.cpp \
        mainwindow.cpp \
    figure.cpp \
    drawfigure.cpp \
    game.cpp \
    objectfigure.cpp \
    gamemap.cpp \
    statewait.cpp \
    stateinmove.cpp \
    statedisappear.cpp \
    statereversmove.cpp \
    stateinmainmenu.cpp \
    stateingame.cpp \
    roundtime.cpp \
    score.cpp \
    recordtable.cpp \
    labelespainter.cpp

HEADERS += \
        mainwindow.h \
    objectphysical.h \
    drawobject.h \
    figure.h \
    drawfigure.h \
    objectfigure.h \
    game.h \
    gamemap.h \
    stategamemap.h \
    statewait.h \
    stateinmove.h \
    statedisappear.h \
    statereversmove.h \
    stategame.h \
    stateinmainmenu.h \
    stateingame.h \
    roundtime.h \
    score.h \
    filesystem.h \
    recordtable.h \
    labelespainter.h

FORMS += \
        mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
