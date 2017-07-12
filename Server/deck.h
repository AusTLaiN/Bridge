#ifndef DECK_H
#define DECK_H

#include <QObject>

#include "Cards/cards.h"

class Deck : public QObject
{
    Q_OBJECT

public:
    static const int CARDS_TO_REMOVE = 2;

public:
    explicit Deck(QObject *parent = 0);
    ~Deck();

    const Card::CardList &getRemaining();
    const Card::CardList &getPlayed();
    const Card::CardList &getGraveyard();

    QStringList toStringList();

signals:
    void cardPlayed(Card *card);

public slots:     
    QSharedPointer<Card> lastPlayed();
    QSharedPointer<Card> takeCard();

    // Adds card to remaining list
    void addToDeck(Card *card);
    // Adds card to played list
    void addToPlayed(Card *card);
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
