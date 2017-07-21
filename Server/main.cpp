#include <QCoreApplication>
#include <QMetaEnum>
#include <QTextStream>

#include "game.h"
#include "deck.h"
#include "actionargs.h"

using namespace bridge_game;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream qcin(stdin);
    QTextStream qcout(stdout);

    qcout << "Server started" << endl;

    Deck deck;

    for (QString& card : deck.toStringList())
    {
        qcout << card << endl;
    }

    deck.shuffle();

    for (QString& card : deck.toStringList())
    {
        qcout << card << endl;
    }

    Game game;

    game.newRound();

    ActionArgs args;
    args.owner = PlayerPtr(new Player());
    args.target = PlayerPtr(new Player());
    args.card = deck.takeCard();

    qcout << args.toString();

    qcout.flush();
    return a.exec();
}
