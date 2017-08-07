#include "player.h"

#include <QDebug>
#include <QJsonArray>

using namespace bridge_game;

QJsonObject Player::serialize(const PlayerPtr &player)
{
    return player->toJson();
}

PlayerPtr Player::deserialize(const QJsonObject &json)
{
    Player *p = new Player(0);
    p->fromJson(json);
    return PlayerPtr(p);
}

void Player::hideCards(QJsonObject &json)
{
    json["cards"] = "Hidden";
}

Player::Player(int id, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_turns_blocked(0),
    m_score(0),
    m_name("Unknown"),
    m_addr("UnknownAddress")
{

}

const CardList& Player::getCards() { return m_cards; }

QString Player::getName() { return m_name; }

QString Player::getAddr() { return m_addr;}

int Player::getScore() { return m_score; }

int Player::getId() { return m_id; }

QJsonObject Player::toJson()
{
    QJsonObject json;

    json["id"] = m_id;
    json["name"] = m_name;
    json["address"] = m_addr;
    json["score"] = m_score;
    json["turns blocked"] = m_turns_blocked;
    json["cards"] = Serializable::listToJson(m_cards, Card::serialize);

    return json;
}

void Player::fromJson(const QJsonObject &json)
{
    m_id = json["id"].toInt();
    m_name = json["name"].toString();
    m_addr = json["address"].toString();
    m_score = json["score"].toInt();
    m_turns_blocked = json["turns blocked"].toInt();
    m_cards = Serializable::listFromJson(m_cards, json["cards"].toArray(), Card::deserialize);
}

int Player::getTurnsBlocked() { return m_turns_blocked; }

void Player::setName(const QString &name) { m_name = name; }

void Player::setAddr(const QString &addr) { m_addr = addr; }


int Player::calculatePoints()
{
    qDebug("Player::calculatePoints");

    int points = 0;

    for (CardPtr card : m_cards)
    {
        points += card->getValue();
    }

    return points;
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

void Player::playCard(ActionArgs args, int card_number)
{
    if (card_number < 0 || card_number > m_cards.count())
    {
        qDebug() << "Player::playCard: invalid card_number";
        return;
    }

    auto card = m_cards[card_number];
    m_cards.removeAt(card_number);
    card->action(args);
}

void Player::playCard(ActionArgs args, CardPtr card)
{
    if (card == nullptr)
    {
        qDebug() << "Player::playCard: card is null";
        return;
    }
    if (!m_cards.contains(card))
    {
        qDebug() << "Player::playCard: card is not in player's hand";
        return;
    }

    playCard(args, m_cards.indexOf(card));
}
