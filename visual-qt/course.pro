#-------------------------------------------------
#
# Project created by QtCreator 2018-04-04T16:28:19
#
#-------------------------------------------------

QT       += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = course
TEMPLATE = app
CONFIG += c++11
#INCLUDEPATH += C:\Qt\boost
#LIBS += -LC:\Qt\boost -lboost

SOURCES += main.cpp\
    loginwindow.cpp \
    userstable.cpp \
    user.cpp \
    exceptions.cpp \
    usermainwindow.cpp \
    editfilm.cpp \
    adminmainwindow.cpp \
    film.cpp \
    Di.cpp

HEADERS  += \
    loginwindow.h \
    userstable.h \
    exceptions.h \
    user.h \
    usermainwindow.h \
    editfilm.h \
    adminmainwindow.h \
    SqlQuery.h \
    film.h \
    Di.h \
    magic.h

FORMS    += \
    loginwindow.ui \
    usermainwindow.ui \
    editfilm.ui \
    adminmainwindow.ui
