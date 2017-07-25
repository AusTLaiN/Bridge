#include "player.h"
#include "standartcardfactory.h"

#include <QDebug>
#include <QJsonArray>

using namespace bridge_game;

Player::Player(int id, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_turns_blocked(0),
    m_score(0),
    m_name("Unknown"),
    m_addr("UnknownAddress")
{

}

const CardList &Player::getCards() { return m_cards; }

QString Player::getName() { return m_name; }

QString Player::getAddr() { return m_addr;}

int Player::getScore() { return m_score; }

QJsonObject Player::toJson()
{
    QJsonObject json;

    json["id"] = m_id;
    json["name"] = m_name;
    json["address"] = m_addr;
    json["score"] = m_score;
    json["turns blocked"] = m_turns_blocked;
    json["cards"] = Serializable::listToJson<CardPtr>(m_cards);

    return json;
}

void Player::fromJson(const QJsonObject &json)
{
    StandartCardFactory factory;

    auto func = [&factory](const QJsonObject &obj) {
        return factory.createCard(obj);
    };

    m_id = json["id"].toInt();
    m_name = json["name"].toString();
    m_addr = json["address"].toString();
    m_score = json["score"].toInt();
    m_turns_blocked = json["turns blocked"].toInt();
    m_cards = Serializable::listFromJson<CardPtr, decltype(func)>(json["cards"].toArray(), func);
}

int Player::getTurnsBlocked() { return m_turns_blocked; }

void Player::setName(const QString &name) { this->m_name = name; }

void Player::setAddr(const QString &addr) { this->m_addr = addr; }


int Player::calculatePoints()
{
    qDebug("Player::calculatePoints");
    return 0;
}

void Player::takeCard(CardPtr card)
{
    m_cards.append(card);
    emit cardTaken(card);
}

void Player::skipTurn()
{
    m_turns_blocked++;
    emit turnSkipped();
}

void Player::takeExtraTurn()
{
    m_turns_blocked--;
    emit extraTurnGained();
}

int Player::addPoints()
{
    for (auto card : m_cards)
    {
        m_score += card.data()->getValue();
    }

    return m_score;
}

int Player::addPoints(int points)
{
    m_score += points;

    return m_score;
}
