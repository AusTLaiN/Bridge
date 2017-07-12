QT += core
QT -= gui

CONFIG += c++11

TARGET = Bridge
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    Server/main.cpp \
    Server/player.cpp \
    Server/deck.cpp \
    Server/game.cpp \
    Server/Cards/card.cpp \
    Server/Cards/six.cpp \
    Server/Actions/abstractaction.cpp \
    Server/Actions/blockturn.cpp \
    Server/Cards/seven.cpp \
    Server/Cards/jack.cpp \
    Server/Cards/eight.cpp \
    Server/Cards/nine.cpp \
    Server/Cards/ten.cpp \
    Server/Cards/queen.cpp \
    Server/Cards/king.cpp \
    Server/Cards/ace.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DISTFILES += \
    .gitignore

HEADERS += \
    Server/player.h \
    Server/deck.h \
    Server/game.h \
    Server/Cards/card.h \
    Server/Cards/six.h \
    Server/Actions/abstractaction.h \
    Server/Cards/cards.h \
    Server/Actions/blockturn.h \
    Server/Cards/seven.h \
    Server/Cards/jack.h \
    Server/Cards/eight.h \
    Server/Cards/nine.h \
    Server/Cards/ten.h \
    Server/Cards/queen.h \
    Server/Cards/king.h \
    Server/Cards/ace.h

