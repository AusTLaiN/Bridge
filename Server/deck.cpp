#include "deck.h"

Deck::Deck(QObject *parent) :
    QObject(parent)
{
}

Deck::~Deck()
{
}

const Card::CardList &Deck::getRemaining() { return remaining; }

const Card::CardList &Deck::getPlayed() { return played; }

const Card::CardList &Deck::getGraveyard() { return graveyard; }

QSharedPointer<Card> Deck::lastPlayed()
{
    return played.last();
}

QSharedPointer<Card> Deck::takeCard()
{
    return remaining.takeFirst();
}

void Deck::addToDeck(Card *card)
{
    remaining.append(QSharedPointer<Card>(card));
}

void Deck::addToPlayed(Card *card)
{
    played.append(QSharedPointer<Card>(card));
}

void Deck::moveToGraveyard(int index)
{
    auto card = played.takeAt(index);
    graveyard.append(card);
}

void Deck::restore()
{
    for (auto card : played)
    {
        remaining.append(card);
    }

    played.clear();
}

void Deck::shake()
{
    qDebug("Deck::shake");
}
