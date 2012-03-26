#-------------------------------------------------
#
# Project created by QtCreator 2012-03-24T16:39:31
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Biblioteca
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    availabledelegate.cpp \
    editbookform.cpp \
    newbookform.cpp \
    newreaderform.cpp \
    editreaderform.cpp \
    newborrowingform.cpp

HEADERS  += mainwindow.h \
    database.h \
    availabledelegate.h \
    editbookform.h \
    newbookform.h \
    newreaderform.h \
    editreaderform.h \
    newborrowingform.h

FORMS    += mainwindow.ui \
    editbookform.ui \
    newbookform.ui \
    newreaderform.ui \
    editreaderform.ui \
    newborrowingform.ui

RESOURCES += \
    Icons.qrc
