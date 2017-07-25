#ifndef ABSTRACTCARDFACTORY_H
#define ABSTRACTCARDFACTORY_H

#include "global.h"
#include "card.h"

namespace bridge_game {

class AbstractCardFactory
{
public:
    AbstractCardFactory();
    virtual ~AbstractCardFactory() = 0;

    virtual CardPtr createCard(Card::Rank rank, Card::Suit suit) = 0;
    virtual CardPtr createCard(const QJsonObject &json) = 0;
};

}


#endif // ABSTRACTCARDFACTORY_H
