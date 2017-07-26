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

    //qcout << deck.toJsonDoc().toJson() << endl;

    deck.shuffle();

    Deck deck2;

    deck2.fromJson(deck.toJson());

    //qcout << deck2.toJsonDoc().toJson() << endl;

    Game game(rand());
    PlayerPtr player1(new Player(rand()));
    PlayerPtr player2(new Player(rand()));

    game.join(player1);
    game.newRound();

    game.takeCards(player1, 3);

    //qcout << game.getPlayer(0)->toJsonDoc().toJson() << endl;
    auto json_p1 = player1->toJson();
    player2->fromJson(json_p1);
    //qcout << player2->toJsonDoc().toJson() << endl;

    qcout << game.toJsonDoc().toJson() << endl;


    qcout.flush();

    return a.exec();
}
