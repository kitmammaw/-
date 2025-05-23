QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BinaryTreeProject_Qt
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    node.h

FORMS += \
    mainwindow.ui

SOURCES += \
    node.cpp
