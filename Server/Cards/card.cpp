#include "card.h"
#include "game.h"
#include "actionargs.h"

#include <QMetaEnum>

using namespace bridge_game;

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
    default:
        return -1;
    }
}

Card::Rank Card::cardRank(int numeric_rank)
{
    return static_cast<Card::Rank>(numeric_rank);
}

QString Card::cardName(Card::Rank card_rank, Card::Suit card_suit)
{
    QMetaEnum metaRank = QMetaEnum::fromType<Card::Rank>();
    QMetaEnum metaSuit = QMetaEnum::fromType<Card::Suit>();

    return QString("Card(%1,%2)").arg(metaRank.valueToKey(card_rank), metaSuit.valueToKey(card_suit));
}

// Static end

Card::Card(Card::Rank rank, Card::Suit suit, QObject *parent) :
    QObject(parent)
{
    setRank(rank);
    setSuit(suit);
    setValue(cardValue(rank));
    setPlayable(true);
}

Card::~Card()
{
}

// Getters and setters

bool Card::isPlayable() { return _playable; }

int Card::getValue() { return _value; }

Card::Suit Card::getSuit() { return _suit; }

Card::Rank Card::getRank() { return _rank; }

void Card::setPlayable(bool playable) { _playable = playable; }

void Card::setValue(int value) { _value = value; }

void Card::setSuit(Card::Suit suit) { _suit = suit; }

void Card::setRank(Card::Rank rank) { _rank = rank; }

// Getters and setters end

QString Card::toString()
{
    return cardName(getRank(), getSuit());
}

void Card::action(ActionArgs args)
{
    qDebug("Card::action:");
    qDebug() << args.toString();
}
