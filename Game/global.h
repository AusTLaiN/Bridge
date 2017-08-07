#ifndef GLOBAL_H
#define GLOBAL_H

#include <QSharedPointer>
#include <QDebug>

#include "serializable.h"

// Global include for almost all files
// Contains class-forwarding, typedefs, aliases

namespace bridge_game {

class Card;

    typedef QSharedPointer<Card> CardPtr;
    typedef QScopedPointer<Card> CardPtrUnique;
    typedef QList<CardPtr> CardList;
    typedef QList<CardPtrUnique> CardListUnique;


class Player;

    typedef QSharedPointer<Player> PlayerPtr;
    typedef QList<PlayerPtr> PlayersList;


class Deck;

    typedef QSharedPointer<Deck> DeckPtr;


struct ActionArgs;
class Game;

    typedef QSharedPointer<Game> GamePtr;

class AbstractCardFactory;

    typedef QSharedPointer<AbstractCardFactory> CardFactoryPtr;

class AbstractDeckFactory;

    typedef QSharedPointer<AbstractDeckFactory> DeckFactoryPtr;

class AbstractAction;

    typedef QSharedPointer<AbstractAction> ActionPtr;


} // namespace bridge_game

namespace bridge_server {

class DataObject;
    typedef QSharedPointer<DataObject> DataObjectPtr;

}

#endif // GLOBAL_H
