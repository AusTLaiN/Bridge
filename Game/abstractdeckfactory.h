#ifndef ABSTRACTDECKFACTORY_H
#define ABSTRACTDECKFACTORY_H

#include "global.h"

namespace bridge_game {

class AbstractDeckFactory
{
public:
    AbstractDeckFactory();
    virtual ~AbstractDeckFactory();

    virtual DeckPtr createDeck() = 0;
    virtual DeckPtr createDeck(const QJsonObject &json) = 0;
};

}



#endif // ABSTRACTDECKFACTORY_H
