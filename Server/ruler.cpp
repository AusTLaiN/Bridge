#include "ruler.h"

using namespace bridge_game;
using namespace bridge_server;

bool Ruler::checkTurn(CardPtr activeCard, CardList turnCards, Card::Suit currentSuit)
{
    if(!turnCards.isEmpty())
    {
        if(!isCombo(turnCards))
        {
            CardPtr overCard = turnCards.at(0);
            if(overCard->getRank() == Card::Rank::Jack)
                return true;
            if(overCard->getRank() == activeCard->getRank())
                return true;
            if(overCard->getSuit() == currentSuit)
                return true;
        }
        else if(checkCombo(turnCards))
        {
            if(turnCards.at(0)->getSuit() == currentSuit ||
               getSpecialComboRank(turnCards) == Card::Rank::Jack)
                return true;
        }
    }

    return false;
}

bool Ruler::checkCombo(CardList turnCards)
{
    Card::Rank rank = turnCards.at(0)->getRank();
    for(auto it : turnCards)
    {
        if(rank != it->getRank())
            return false;
    }

    return true;
}

Card::Rank Ruler::getSpecialComboRank(CardList turnCards)
{
    if(isCombo(turnCards))
    {
        Card::Rank rank = turnCards.at(0)->getRank();
        if(rank == Card::Rank::Seven ||
           rank == Card::Rank::Eight ||
           rank == Card::Rank::Jack  ||
           rank == Card::Rank::Ace)
            return rank;
    }

    return Card::Rank::UndefinedRank;
}

bool Ruler::isCombo(CardList turnCards)
{
    return turnCards.count() > 1;
}
