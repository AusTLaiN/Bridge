#ifndef STANDARTCARDFACTORY_H
#define STANDARTCARDFACTORY_H

#include "global.h"
#include "abstractcardfactory.h"

namespace bridge_game {

class StandartCardFactory : public AbstractCardFactory
{
public:
    StandartCardFactory();

    // AbstractCardFactory interface

    virtual CardPtr createCard(Card::Rank rank, Card::Suit suit) override;
    virtual CardPtr createCard(const QJsonObject &json) override;
};

}



#endif // STANDARTCARDFACTORY_H
