#ifndef ACTIONARGS_H
#define ACTIONARGS_H

#include "global.h"

namespace bridge_game {

struct ActionArgs
{
    GamePtr game;

    PlayerPtr owner;
    PlayerPtr target;

    CardPtr card;

    QString toString();
};


} // bridge_game


#endif // ACTIONARGS_H
