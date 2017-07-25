#include <QCoreApplication>
#include <QJsonDocument>
#include <QMetaEnum>
#include <QTextStream>

#include "game.h"
#include "deck.h"
#include "actionargs.h"

using namespace bridge_game;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QTextStream qcin(stdin);
    QTextStream qcout(stdout);

    qcout << "Server started" << endl;

    Deck deck;

    qcout << deck.toJsonDoc().toJson() << endl;

    deck.shuffle();

    Deck deck2;

    deck2.fromJson(deck.toJson());

    qcout << deck2.toJsonDoc().toJson() << endl;

    Game game(rand());

    game.join(PlayerPtr(new Player(rand())));
    game.newRound();

    qcout << game.getPlayer(0)->toJsonDoc().toJson() << endl;


    qcout.flush();

    return a.exec();
}
