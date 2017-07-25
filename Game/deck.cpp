#include "deck.h"
#include "standartcardfactory.h"

#include <QJsonArray>
#include <QMetaEnum>

using namespace bridge_game;

Deck::Deck(QObject *parent) :
    QObject(parent)
{
    QMetaEnum suits = QMetaEnum::fromType<Card::Suit>();

    for (int i = 0; i < 4; ++i)
    {
        auto suit = static_cast<Card::Suit>(suits.value(i));

        m_remaining.append(CardPtr(new Six(suit)));
        //remaining.append(CardPtr(new Seven(suit)));
        m_remaining.append(CardPtr(new Eight(suit)));
        //remaining.append(CardPtr(new Nine(suit)));
        //remaining.append(CardPtr(new Ten(suit)));
        m_remaining.append(CardPtr(new Jack(suit)));
        //remaining.append(CardPtr(new Queen(suit)));
        //remaining.append(CardPtr(new King(suit)));
        //remaining.append(CardPtr(new Ace(suit)));
    }
}

Deck::~Deck()
{
}

const CardList &Deck::getRemaining() { return m_remaining; }

const CardList &Deck::getPlayed() { return m_played; }

const CardList &Deck::getGraveyard() { return m_graveyard; }

QJsonObject Deck::toJson()
{
    QJsonObject json;

    json["remaining"] = Serializable::listToJson<CardPtr>(m_remaining);
    json["played"] = Serializable::listToJson<CardPtr>(m_played);
    json["graveyard"] = Serializable::listToJson<CardPtr>(m_graveyard);

    return json;
}

void Deck::fromJson(const QJsonObject &json)
{
    StandartCardFactory factory;

    QJsonArray remArray = json["remaining"].toArray(),
               playedArray = json["played"].toArray(),
               graveArray = json["graveyard"].toArray();

    auto func = [&factory](const QJsonObject &obj) {
        return factory.createCard(obj);
    };

    m_remaining = Serializable::listFromJson<CardPtr, decltype(func)>(remArray, func);
    m_played = Serializable::listFromJson<CardPtr, decltype(func)>(playedArray, func);
    m_graveyard = Serializable::listFromJson<CardPtr, decltype(func)>(graveArray, func);
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
    m_remaining.append(card);
}

void Deck::addToPlayed(CardPtr card)
{
    m_played.append(card);
}

void Deck::moveToGraveyard(int index)
{
    auto card = m_played.takeAt(index);
    m_graveyard.append(card);
}

void Deck::moveToGraveyard(CardPtr card)
{
    m_played.removeAll(card);
    m_graveyard.append(card);
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
    //qDebug() << "Remaining count : " << m_remaining.count();

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
