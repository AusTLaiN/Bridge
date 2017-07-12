#ifndef DECK_H
#define DECK_H

#include <QObject>

#include "Server/card.h"

class Deck : public QObject
{
    Q_OBJECT

public:
    static Deck createDefault();

public:
    explicit Deck(QObject *parent = 0);
    ~Deck();

    Card::CardList getRemaining();
    Card::CardList getPlayed();
    Card::CardList getGraveyard();

signals:
    // No signals

public slots:     
    QSharedPointer<Card> lastPlayed();
    QSharedPointer<Card> takeCard();

    // Adds card to remaining list
    void addToDeck(Card* card);
    // Adds card to played list
    void addToPlayed(Card* card);
    // Moves card from played to graveyard
    void moveToGraveyard(int index);

    // Moves played cards back to remaining
    void restore();
    // Shuffles deck
    void shake();

protected:
    Card::CardList remaining;
    Card::CardList played;
    // Cards that are completely out of the game
    Card::CardList graveyard;
};

#endif // DECK_H
