#include "deck.h"

#include <QMetaEnum>

Deck::Deck(QObject *parent) :
    QObject(parent)
{
    QMetaEnum suits = QMetaEnum::fromType<Card::Suit>();

    for (int i = 1; i < suits.keyCount(); ++i)
    {
        auto suit = static_cast<Card::Suit>(suits.value(i));

        remaining.append(CardPtr(new Six(suit)));
        remaining.append(CardPtr(new Seven(suit)));
        remaining.append(CardPtr(new Eight(suit)));
        remaining.append(CardPtr(new Nine(suit)));
        remaining.append(CardPtr(new Ten(suit)));
        remaining.append(CardPtr(new Jack(suit)));
        remaining.append(CardPtr(new Queen(suit)));
        remaining.append(CardPtr(new King(suit)));
        remaining.append(CardPtr(new Ace(suit)));
    }
}

Deck::~Deck()
{
}

const CardList &Deck::getRemaining() { return remaining; }

const CardList &Deck::getPlayed() { return played; }

const CardList &Deck::getGraveyard() { return graveyard; }

QStringList Deck::toStringList()
{
    QStringList list;

    for (auto card : remaining)
    {
        list << card.data()->toString();
    }

    return list;
}

CardPtr Deck::lastPlayed()
{
    return played.last();
}

CardPtr Deck::takeCard()
{
    if (!remaining.empty())
        return remaining.takeFirst();

    emit noCardsLeft();
    return CardPtr(nullptr);
}

void Deck::addToDeck(CardPtr card)
{
    remaining.append(card);
}

void Deck::addToPlayed(CardPtr card)
{
    played.append(card);
}

void Deck::moveToGraveyard(int index)
{
    auto card = played.takeAt(index);
    graveyard.append(card);
}

void Deck::moveToGraveyard(CardPtr card)
{
    played.removeAll(card);
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

    CardList new_list;

    for (int i = remaining.count(); i > 0; --i)
    {
        int index = rand() % remaining.count();

        auto card = remaining.takeAt(index);
        new_list.append(card);

        qDebug() << "i = " << i << " Index = " << index << " Remaining = " << remaining.count();
    }

    remaining = new_list;
}
