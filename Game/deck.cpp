#include "deck.h"
#include "standartcardfactory.h"

#include <QJsonArray>
#include <QMetaEnum>

using namespace bridge_game;

Deck::Deck(QObject *parent) :
    QObject(parent)
{

}

Deck::~Deck()
{

}

const CardList& Deck::getRemaining() { return m_remaining; }

const CardList& Deck::getPlayed() { return m_played; }

const CardList& Deck::getGraveyard() { return m_graveyard; }

QJsonObject Deck::toJson()
{
    QJsonObject json;

    json["remaining"] = Serializable::listToJson(m_remaining, Card::serialize);
    json["played"] = Serializable::listToJson(m_played, Card::serialize);
    json["graveyard"] = Serializable::listToJson(m_graveyard, Card::serialize);

    return json;
}

void Deck::fromJson(const QJsonObject &json)
{
    QJsonArray remArray = json["remaining"].toArray(),
               playedArray = json["played"].toArray(),
               graveArray = json["graveyard"].toArray();

    Serializable::listFromJson(m_remaining, remArray, Card::deserialize);
    Serializable::listFromJson(m_played, playedArray, Card::deserialize);
    Serializable::listFromJson(m_graveyard, graveArray, Card::deserialize);
}

CardPtr Deck::lastPlayed()
{
    return m_played.last();
}

CardPtr Deck::takeCard()
{
    if (!m_remaining.empty())
        return m_remaining.takeFirst();

    emit noCardsLeft();
    return CardPtr(nullptr);
}

void Deck::addToDeck(CardPtr card)
{
    if (card == nullptr)
        qDebug() << "Deck::addToDeck card is null";
    else
    {
        m_remaining.append(card);
        emit newCardAdded(card);
    }
}

void Deck::addToPlayed(CardPtr card)
{
    if (card == nullptr)
    {
        qDebug() << "Deck::addToPlayed: card is null";
    }
    else
    {
        m_played.append(card);
    }
}

void Deck::moveToGraveyard(int index)
{
    auto card = m_played.takeAt(index);

    if (card == nullptr)
        qDebug() << "Deck::moveToGraveyard: card is null";
    else
        m_graveyard.append(card);
}

void Deck::moveToGraveyard(CardPtr card)
{
    if (card == nullptr)
    {
        qDebug() << "Deck::moveToGraveyard: card is null";
    }
    else if (!m_played.contains(card))
    {
        qDebug() << "Deck::moveToGraveyard: played list does not contain card";
    }
    else
    {
        m_played.removeAll(card);
        m_graveyard.append(card);
    }
}

void Deck::restore()
{
    for (auto card : m_played)
    {
        m_remaining.append(card);
    }

    m_played.clear();
}

void Deck::shuffle()
{
    qDebug("Deck::shuffle");
    qDebug() << "Remaining count : " << m_remaining.count();

    CardList new_list;

    for (int i = m_remaining.count(); i > 0; --i)
    {
        int index = rand() % m_remaining.count();

        auto card = m_remaining.takeAt(index);
        new_list.append(card);

        //qDebug() << "i = " << i << " Index = " << index << " Remaining = " << m_remaining.count();
    }

    m_remaining = new_list;
}

bool Deck::empty()
{
    return m_remaining.empty();
}
