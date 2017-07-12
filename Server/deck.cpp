#include "deck.h"

#include <QMetaEnum>

Deck::Deck(QObject *parent) :
    QObject(parent)
{
    QMetaEnum suits = QMetaEnum::fromType<Card::Suit>();

    for (int i = 0; i < suits.keyCount(); ++i)
    {
        auto suit = static_cast<Card::Suit>(suits.value(i));

        remaining.append(QSharedPointer<Card>(new Six(suit)));
        remaining.append(QSharedPointer<Card>(new Seven(suit)));
        remaining.append(QSharedPointer<Card>(new Eight(suit)));
        remaining.append(QSharedPointer<Card>(new Nine(suit)));
        remaining.append(QSharedPointer<Card>(new Ten(suit)));
        remaining.append(QSharedPointer<Card>(new Jack(suit)));
        remaining.append(QSharedPointer<Card>(new Queen(suit)));
        remaining.append(QSharedPointer<Card>(new King(suit)));
        remaining.append(QSharedPointer<Card>(new Ace(suit)));
    }
}

Deck::~Deck()
{
}

const Card::CardList &Deck::getRemaining() { return remaining; }

const Card::CardList &Deck::getPlayed() { return played; }

const Card::CardList &Deck::getGraveyard() { return graveyard; }

QStringList Deck::toStringList()
{
    QStringList list;

    for (auto card : remaining)
    {
        list << card.data()->toString();
    }

    return list;
}

QSharedPointer<Card> Deck::lastPlayed()
{
    return played.last();
}

QSharedPointer<Card> Deck::takeCard()
{
    if (!remaining.empty())
        return remaining.takeFirst();

    for (int i = 0; i < CARDS_TO_REMOVE; ++i)
    {
        moveToGraveyard(played.count() - 1);
    }

    remaining.append(played);
    played.clear();
    shake();
    return takeCard();
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
    qDebug() << "Remaining count : " << remaining.count();

    Card::CardList new_list;

    for (int i = remaining.count(); i > 0; --i)
    {
        int index = rand() % remaining.count();

        auto card = remaining.takeAt(index);
        new_list.append(card);

        qDebug() << "i = " << i << " Index = " << index << " Remaining = " << remaining.count();
    }

    remaining = new_list;
}
