#include "six.h"

Six::Six(Card::Suit suit, QObject *parent) :
    Card(parent)
{
    setRank(Card::Six);
    setSuit(suit);
    init();
}

void Six::action()
{
    qDebug("Six::action");
}
