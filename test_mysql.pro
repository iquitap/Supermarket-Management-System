#-------------------------------------------------
#
# Project created by QtCreator 2017-05-11T11:17:59
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_mysql
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    saleman.cpp \
    manager.cpp \
    goodsman.cpp \
    change_inf.cpp

HEADERS  += mainwindow.h \
    saleman.h \
    manager.h \
    goodsman.h \
    change_inf.h
# HEADERS  += "/usr/local/opt/mysql/include/mysql.h"

FORMS    += mainwindow.ui \
    saleman.ui \
    manager.ui \
    goodsman.ui \
    change_inf.ui

# INCLUDEPATH += "/usr/local/opt/mysql/include"
# LIBS += "/usr/local/opt/mysql/*"
