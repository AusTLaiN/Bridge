#include "card.h"
#include "game.h"
#include "actionargs.h"
#include "standartcardfactory.h"

#include <QMetaEnum>

using namespace bridge_game;

// Static functions

int Card::cardValue(Card::Rank card_rank, Card::Suit suit)
{
    if (suit == Suit::AnySuit || suit == Suit::UndefinedSuit)
        return -1;

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

QString Card::toString(Card::Rank rank)
{
    QMetaEnum metaRank = QMetaEnum::fromType<Rank>();

    return QString(metaRank.valueToKey(rank));
}

QString Card::toString(Card::Suit suit)
{
    QMetaEnum metaSuit = QMetaEnum::fromType<Suit>();

    return QString(metaSuit.valueToKey(suit));
}

QJsonObject Card::serialize(const CardPtr &card)
{
    return card->toJson();
}

CardPtr Card::deserialize(const QJsonObject &json)
{
    return StandartCardFactory().createCard(json);
}

// Static end

Card::Card(Card::Rank rank, Card::Suit suit, QObject *parent) :
    QObject(parent),
    m_rank(rank),
    m_suit(suit)
{
    m_value = cardValue(m_rank, m_suit);
    m_playable = m_value > -1;
}

Card::~Card()
{
}

// Getters and setters

bool Card::isPlayable() { return m_playable; }

int Card::getValue() { return m_value; }

Card::Suit Card::getSuit() { return m_suit; }

Card::Rank Card::getRank() { return m_rank; }

void Card::setPlayable(bool playable) { m_playable = playable; }

/*void Card::setValue(int value) { m_value = value; }

void Card::setSuit(Card::Suit suit) { m_suit = suit; }

void Card::setRank(Card::Rank rank) { m_rank = rank; }*/

// Getters and setters end

QJsonObject Card::toJson()
{
    QJsonObject json;

    json["playable"] = m_playable;
    json["value"] = m_value;
    json["rank"] = m_rank;
    json["suit"] = m_suit;

    json["name"] = toString(m_rank) + " " + toString(m_suit);

    return json;
}

void Card::fromJson(const QJsonObject &json)
{
    /*m_playable = json["playbale"].toBool();
    m_value = json["value"].toInt();
    m_rank = static_cast<Rank>(json["rank"].toInt());
    m_suit = static_cast<Suit>(json["suit"].toInt());*/

    qDebug() << "Card::fromJson: Deserialization of abstract class is not possible";
}

void Card::action(ActionArgs args)
{
    qDebug("Card::action:");
}
