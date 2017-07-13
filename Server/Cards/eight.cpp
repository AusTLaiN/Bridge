#include "eight.h"

#include "Server/game.h"
#include "Server/player.h"
#include "Server/deck.h"

Eight::Eight(Suit suit, QObject *parent) :
    Card(Card::Eight, suit, parent)
{

}

void Eight::action(Game *game)
{
    Card::action(game);

    auto target = game->getNextPlayer();
    auto deck = game->getDeck();

    qDebug() << "Target : " << target->toString();

    target->skipTurn();
    target->takeCard(deck->takeCard());
}
