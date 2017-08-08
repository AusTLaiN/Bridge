QT += core websockets
QT -= gui

CONFIG += c++11

TARGET = Bridge
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    Game/Cards/ace.cpp \
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
    Game/player.cpp \
    Game/serializable.cpp \
    Game/standartcardfactory.cpp \
    Game/abstractaction.cpp \
    Game/standartdeckfactory.cpp \
    Game/Actions/actiontakecard.cpp \
    Game/Actions/actionskipturn.cpp \
    Game/Actions/actionrefilldeck.cpp \
    Game/Actions/actiongamestart.cpp \
    Game/abstractcardfactory.cpp \
    Game/abstractdeckfactory.cpp \
    Game/Actions/actionsetactivesuit.cpp \
    Server/server.cpp \
    Server/command.cpp \
    Server/ruler.cpp \
    Server/DataObjects/dataobject.cpp \
    Server/DataObjects/htmldataobject.cpp \
    Server/DataObjects/intdataobject.cpp \
    Server/DataObjects/flagdataobject.cpp \
    Server/DataObjects/cardlistdataobject.cpp \
    Server/dataobjectfactory.cpp \
    Server/message.cpp

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
    Game/player.h \
    Game/serializable.h \
    Game/abstractcardfactory.h \
    Game/standartcardfactory.h \
    Game/abstractaction.h \
    Game/abstractdeckfactory.h \
    Game/standartdeckfactory.h \
    Game/Actions/actiontakecard.h \
    Game/Actions/actionskipturn.h \
    Game/Actions/actions.h \
    Game/Actions/actionrefilldeck.h \
    Game/Actions/actiongamestart.h \
    Game/Actions/actionsetactivesuit.h \
    Server/command.h \
    Server/DataObjects/dataobject.h \
    Server/dataobjectfactory.h \
    Server/message.h \
    Server/ruler.h \
    Server/server.h \
    Server/DataObjects/htmldataobject.h \
    Server/DataObjects/intdataobject.h \
    Server/DataObjects/flagdataobject.h \
    Server/DataObjects/cardlistdataobject.h

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
    Client/new 1.html \
    Server/Readme.txt

INCLUDEPATH += \
        $$PWD/Server \
        $$PWD/Game
