#include "actionskipturn.h"
#include "game.h"

using namespace bridge_game;


ActionSkipTurn::ActionSkipTurn(Game *game, QObject *parent) :
    AbstractAction(game, parent)
{
    m_name = "ActionSkipTurn";
}

void ActionSkipTurn::execute()
{
    if (!checkTargetType())
    {
        qDebug() << "ActionSkipTurn::execute: invalid target type"
                 << "Target type = " << m_target_type
                 << "Number of targets = " << m_targets.count();
    }

    //qDebug() << "ActionSkipTurn::execute: start";

    for (Player *player : m_targets)
    {
        player->skipTurn();
    }

    //qDebug() << "ActionSkipTurn::execute: end";
}
