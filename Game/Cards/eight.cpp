#include "eight.h"
#include "game.h"

using namespace bridge_game;

Eight::Eight(Suit suit, QObject *parent) :
    Card(Card::Eight, suit, parent)
{

}

void Eight::action(ActionArgs args)
{
    Card::action(args);

    auto target = args.target;
    auto deck = args.game->getDeck();

    target->skipTurn();
    target->takeCard(deck->takeCard());
}
