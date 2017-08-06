#include "actiongamestart.h"
#include "game.h"
#include "actiontakecard.h"

using namespace bridge_game;


ActionGameStart::ActionGameStart(Game *game, QObject *parent) :
    AbstractAction(game, parent)
{
    m_name = "ActionGameStart";
}

void ActionGameStart::execute()
{
    if (!checkTargetType())
    {
        qDebug() << "ActionGameStart::execute: invalid target type"
                 << "Target type = " << m_target_type
                 << "Number of targets = " << m_targets.count();
    }

    //qDebug() << "ActionGameStart::execute: start";

    auto deck = m_game->getDeck();

    for (Player *player : m_targets)
    {
        for (int i = 0; i < Game::CARDS_START_WITH; ++i)
        {
            auto card = deck->takeCard();
            if (card == nullptr)
            {
                qDebug() << "ActionTakeCard::execute: card is null";
                continue;
            }

            player->takeCard(card);
        }
    }

    //qDebug() << "ActionGameStart::execute: end";
}
