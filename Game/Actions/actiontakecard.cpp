#include "actiontakecard.h"
#include "game.h"

using namespace bridge_game;

ActionTakeCard::ActionTakeCard(Game *game, QObject *parent) :
    AbstractAction(game, parent)
{
    m_name = "ActionTakeCard";
}

void ActionTakeCard::execute()
{
    if (!checkTargetType())
    {
        qDebug() << "ActionTakeCard::execute: invalid target type"
                 << "Target type = " << m_target_type
                 << "Number of targets = " << m_targets.count();
    }

    //qDebug() << "ActionTakeCard::execute: start";

    auto deck = m_game->getDeck().data();

    for (Player *player : m_targets)
    {
        auto card = deck->takeCard();
        if (card == nullptr)
        {
            qDebug() << "ActionTakeCard::execute: card is null";
            continue;
        }

        player->takeCard(card);
    }

    //qDebug() << "ActionTakeCard::execute: end";
}
