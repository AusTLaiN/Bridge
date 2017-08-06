#include "actionrefilldeck.h"
#include "game.h"

using namespace bridge_game;

ActionRefillDeck::ActionRefillDeck(Game *game, QObject *parent) :
    AbstractAction(game, parent)
{
    m_name = "ActionRefillDeck";
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

    auto last_card = deck->lastPlayed();
    deck->restore();
    deck->shuffle();
    deck->removeCard(last_card);
    deck->addToPlayed(last_card);

    for (int i = 0; i < Game::CARDS_TO_REMOVE; ++i)
    {
        deck->moveToGraveyard(deck->takeCard());
    }
}
