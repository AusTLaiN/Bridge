#include "player.h"

#include <QDebug>

Player::Player(QObject *parent) :
    QObject(parent),
    cards(new Card::CardList)
{

}

Card::CardList *Player::getCards() { return cards; }

QString Player::getName() { return name; }

QString Player::getAddr() { return addr;}

int Player::getScore() { return score; }

QString Player::toString()
{
    return QString("Player(Name=%1,Address=%2)").arg(name, addr);
}

int Player::getTurnsBlocked() { return turns_blocked; }

void Player::setName(const QString &name) { this->name = name; }

void Player::setAddr(const QString &addr) { this->addr = addr; }


int Player::calculatePoints()
{
    qDebug("Player::calculatePoints");
}

void Player::addCard(Card *card)
{
    cards->append(QSharedPointer<Card>(card));
}

void Player::addCard(QSharedPointer<Card> card)
{
    cards->append(card);
}

void Player::skipTurn()
{
    turns_blocked++;
}

int Player::addPoints()
{
    for (auto card : *cards)
    {
        score += card.data()->getValue();
    }

    return score;
}

int Player::addPoints(int points)
{
    score += points;

    return score;
}
