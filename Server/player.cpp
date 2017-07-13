#include "player.h"

#include <QDebug>

Player::Player(QObject *parent) :
    QObject(parent)
{

}

const CardList &Player::getCards() { return cards; }

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

void Player::takeCard(CardPtr card)
{
    cards.append(card);
    emit cardTaken(card);
}

void Player::skipTurn()
{
    turns_blocked++;
    emit turnSkipped();
}

void Player::takeExtraTurn()
{
    turns_blocked--;
    emit extraTurnGained();
}

int Player::addPoints()
{
    for (auto card : cards)
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
