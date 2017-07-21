#include <QCoreApplication>
#include <QMetaEnum>
#include <QTextStream>

#include "Server/game.h"
#include "Server/deck.h"
#include "Server/server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QTextStream qcin(stdin);
    QTextStream qcout(stdout);

    qcout << "Server started" << endl;

    Deck deck;

    for (QString& card : deck.toStringList())
    {
        qcout << card << endl;
    }

    deck.shake();

    for (QString& card : deck.toStringList())
    {
        qcout << card << endl;
    }

    Game game;

    game.newRound();

    qcout.flush();

    Server server(8080);

    return a.exec();
}
