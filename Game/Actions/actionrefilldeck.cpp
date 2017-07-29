#include "actionrefilldeck.h"
#include "game.h"

using namespace bridge_game;

ActionRefillDeck::ActionRefillDeck(Game *game, QObject *parent) :
    AbstractAction(game, parent)
{

}

void ActionRefillDeck::execute()
{
    auto deck = m_game->getDeck();

    if (!deck)
    {
        qDebug() << "ActionRefillDeck::execute: deck is null";
        return;
    }
    if (!deck->empty())
    {
        qDebug() << "ActionRefillDeck::execute: deck is not empty";
        return;
    }

    // A bug here
    // We need to left on board last played card

    auto last_card = deck->lastPlayed();
    deck->restore();
    deck->shuffle();

    for (int i = 0; i < Game::CARDS_TO_REMOVE; ++i)
    {
        deck->moveToGraveyard(deck->takeCard());
    }

    //deck->addToPlayed(card);
}
