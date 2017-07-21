#include "player.h"

#include <QDebug>

using namespace bridge_game;

Player::Player(QObject *parent) :
    QObject(parent),
    turns_blocked(0),
    score(0),
    name("Unknown"),
    addr("NoAddress")
{

}

const CardList &Player::getCards() { return cards; }

QString Player::getName() { return name; }

QString Player::getAddr() { return addr;}

int Player::getScore() { return score; }

QString Player::toString()
{
    auto str_turns = QString::number(turns_blocked);
    auto str_score = QString::number(score);

    return QString("Player(Name=%1, Address=%2, "
                   "TurnsBlocked=%3, Score=%4)").arg(name, addr, str_turns, str_score);
}

int Player::getTurnsBlocked() { return turns_blocked; }

void Player::setName(const QString &name) { this->name = name; }

void Player::setAddr(const QString &addr) { this->addr = addr; }


int Player::calculatePoints()
{
    qDebug("Player::calculatePoints");
    return 0;
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
