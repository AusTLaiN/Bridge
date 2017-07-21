#include "actionargs.h"
#include "game.h"


QString bridge_game::ActionArgs::toString()
{
    QStringList list;

    list << "ActionArgs : "
         << QString().sprintf("Game : %08p", game.data())
         << QString().sprintf("Owner : %08p", owner.data())
         << owner->toString()
         << QString().sprintf("Target : %08p", target.data())
         << target->toString()
         << QString().sprintf("Card : %08p", card.data())
         << card->toString();

    return list.join("\n");
}
