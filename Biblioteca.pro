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
    newreaderform.cpp

HEADERS  += mainwindow.h \
    database.h \
    availabledelegate.h \
    editbookform.h \
    newbookform.h \
    newreaderform.h

FORMS    += mainwindow.ui \
    editbookform.ui \
    newbookform.ui \
    newreaderform.ui

RESOURCES += \
    Icons.qrc
