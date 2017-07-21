#include "jack.h"

using namespace bridge_game;

Jack::Jack(Suit suit, QObject *parent) :
    Card(Card::Jack, suit, parent)
{
}
