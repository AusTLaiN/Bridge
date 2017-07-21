QT += core
QT -= gui

CONFIG += c++11

TARGET = Bridge
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    Game/Cards/ace.cpp \
    Game/Cards/actionargs.cpp \
    Game/Cards/eight.cpp \
    Game/Cards/jack.cpp \
    Game/Cards/king.cpp \
    Game/Cards/nine.cpp \
    Game/Cards/queen.cpp \
    Game/Cards/seven.cpp \
    Game/Cards/six.cpp \
    Game/Cards/ten.cpp \
    Game/card.cpp \
    Game/deck.cpp \
    Game/game.cpp \
    Game/main.cpp \
    Game/player.cpp

HEADERS += \
    Game/Cards/ace.h \
    Game/Cards/cards.h \
    Game/Cards/eight.h \
    Game/Cards/jack.h \
    Game/Cards/king.h \
    Game/Cards/nine.h \
    Game/Cards/queen.h \
    Game/Cards/seven.h \
    Game/Cards/six.h \
    Game/Cards/ten.h \
    Game/actionargs.h \
    Game/card.h \
    Game/deck.h \
    Game/game.h \
    Game/global.h \
    Game/player.h

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
    .gitignore \
    Client/css/style.css \
    Client/new 1.html \
    3rd-party/Readme.txt \
    Server/Readme.txt \
    Client/new 1.html

INCLUDEPATH += \
        $$PWD/Server \
        $$PWD/Game
