#ifndef RULER_H
#define RULER_H

#include "global.h"
#include "command.h"
#include "card.h"

using namespace bridge_game;

namespace bridge_server
{

class Ruler
{
public:
    static bool checkTurn(CardPtr activeCard, CardList turnCards, Card::Suit currentSuit = Card::Suit::UndefinedSuit);
    static bool checkCombo(CardList turnCards);
    static Card::Rank getSpecialComboRank(CardList turnCards);
    static bool isCombo(CardList turnCards);
};

} // bridge_server
#endif // RULER_H
