#include <QCoreApplication>
#include <QJsonDocument>
#include <QMetaEnum>
#include <QTextStream>

#include "game.h"
#include "deck.h"
#include "actionargs.h"

#include "server.h"
#include "ruler.h"

using namespace bridge_game;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QTextStream qcin(stdin);
    QTextStream qcout(stdout);

    qcout << "Server started" << endl;

    Game game(rand());
    PlayerPtr player1(new Player(rand()));
    PlayerPtr player2(new Player(rand()));

    game.join(player1);
    game.join(player2);
    game.newRound();
    game.playCard(0, 4);
    game.playCard(1, 2);
    //qcout << game.toJsonDoc().toJson() << endl;

    /*GamePtr game(new Game(rand()));

    PlayerPtr player1(new Player(rand()));
    PlayerPtr player2(new Player(rand()));

    game->join(player1);
    game->join(player2);
    game->newRound();
    game->playCard(0, 4);

    qcout << game->toJsonDoc().toJson() << endl;*/


    qcout.flush();

    bridge_server::Server server(8080);

    return a.exec();
}
