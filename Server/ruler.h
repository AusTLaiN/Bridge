#ifndef RULER_H
#define RULER_H

#include "global.h"
#include "command.h"
#include "card.h"

namespace bridge_server
{

class Ruler
{
public:
    static bool checkTurn(bridge_game::CardPtr activeCard, bridge_game::CardList turnCards, bridge_game::Card::Suit currentSuit = bridge_game::Card::Suit::UndefinedSuit);
    static bool checkCombo(bridge_game::CardList turnCards);
    static bridge_game::Card::Rank getSpecialComboRank(bridge_game::CardList turnCards);
    static bool isCombo(bridge_game::CardList turnCards);
};

} // bridge_server

#endif // RULER_H
