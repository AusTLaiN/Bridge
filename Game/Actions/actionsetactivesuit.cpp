#include "actionsetactivesuit.h"
#include "game.h"

using namespace bridge_game;

ActionSetActiveSuit::ActionSetActiveSuit(Game *game, Card::Suit suit, QObject *parent) :
    AbstractAction(game, parent)
{
    m_name = "ActionSetActiveSuit";
    m_suit = suit;
}

void ActionSetActiveSuit::execute()
{
    if (m_suit == Card::UndefinedSuit || m_suit == Card::AnySuit)
    {
        qDebug() << "ActionSetActiveSuit::execute: Invalid card suit" << endl
                 << "Card suit : " << m_suit;
    }

    m_game->setActiveSuit(m_suit);
}
