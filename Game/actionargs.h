#ifndef ACTIONARGS_H
#define ACTIONARGS_H

#include "global.h"

namespace bridge_game {

struct ActionArgs
{
    ActionArgs() :
        game(nullptr),
        made_by(nullptr)
    {

    }

    Game *game;
    Player *made_by;
};


} // bridge_game


#endif // ACTIONARGS_H
