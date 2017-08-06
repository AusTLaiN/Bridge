#ifndef STANDARTDECKFACTORY_H
#define STANDARTDECKFACTORY_H

#include "global.h"
#include "abstractdeckfactory.h"

namespace bridge_game {

class StandartDeckFactory : public AbstractDeckFactory
{
public:
    StandartDeckFactory();

    virtual DeckPtr createDeck() override;
    virtual DeckPtr createDeck(const QJsonObject &json) override;
};

}



#endif // STANDARTDECKFACTORY_H
