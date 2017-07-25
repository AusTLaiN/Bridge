#ifndef GLOBAL_H
#define GLOBAL_H

#include <QSharedPointer>

#include "serializable.h"

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

} // namespace bridge_game


#endif // GLOBAL_H
