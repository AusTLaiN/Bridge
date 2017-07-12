#include "card.h"

#include <QMetaEnum>

// Static functions

int Card::cardValue(Card::Rank card_rank)
{
    switch(card_rank) {
    case Six:
    case Seven:
    case Eight:
    case Nine:
        return 0;
    case Ten:
        return 10;
    case Jack:
        return 20;
    case Queen:
    case King:
        return 10;
    case Ace:
        return 15;
    }

    return -1;
}

Card::Rank Card::cardRank(int numeric_rank)
{
    return static_cast<Card::Rank>(numeric_rank);
}

QString Card::cardName(Card::Rank card_rank, Card::Suit card_suit)
{
    QMetaEnum metaRank = QMetaEnum::fromType<Card::Rank>();
    QMetaEnum metaSuit = QMetaEnum::fromType<Card::Suit>();

    return QString("Card(%1 %2)").arg(metaRank.key(card_rank), metaSuit.key(card_suit));
}

// Static end

Card::Card(QObject *parent) :
    QObject(parent),
    _playable(false),
    _name("Unknown"),
    _value(-1)
{
}

Card::~Card()
{
}


bool Card::isPlayable() { return _playable; }

int Card::getValue() { return _value; }

QString Card::getName() { return _name; }

Card::Suit Card::getSuit() { return _suit; }

Card::Rank Card::getRank() { return _rank; }

void Card::setPlayable(bool playable) { _playable = playable; }

void Card::setValue(int value) { _value = value; }

void Card::setName(const QString &name) { _name = name; }

void Card::setSuit(Card::Suit suit) { _suit = suit; }

void Card::setRank(Card::Rank rank) { _rank = rank; }


void Card::init()
{
    setValue(cardValue(getRank()));
    setName(cardName(getRank(), getSuit()));
    setPlayable(true);
}
