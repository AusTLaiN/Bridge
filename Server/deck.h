#ifndef DECK_H
#define DECK_H

#include <QObject>

#include "global.h"
#include "Cards/cards.h"

namespace bridge_game {

class Deck : public QObject
{
    Q_OBJECT

public:
    explicit Deck(QObject *parent = 0);
    ~Deck();

    const CardList &getRemaining();
    const CardList &getPlayed();
    const CardList &getGraveyard();

    QStringList toStringList();

signals:
    void noCardsLeft();

public slots:
    CardPtr lastPlayed();
    CardPtr takeCard();

    // Adds card to remaining list
    void addToDeck(CardPtr card);
    // Adds card to played list
    void addToPlayed(CardPtr card);
    // Moves card from played to graveyard
    void moveToGraveyard(int index);
    void moveToGraveyard(CardPtr card);

    // Moves played cards back to remaining
    void restore();
    // Shuffles deck
    void shuffle();

protected:
    CardList remaining;
    CardList played;
    // Cards that are completely out of the game
    CardList graveyard;
};

} // bridge_game


#endif // DECK_H
