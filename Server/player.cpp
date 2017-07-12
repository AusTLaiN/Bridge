#include "player.h"

#include <QDebug>

Player::Player(QObject *parent) : QObject(parent)
{

}

const Card::CardList &Player::getCards() { return cards; }

QString Player::getName() { return name; }

QString Player::getAddr() { return addr;}

int Player::getTurnsBlocked() { return turns_blocked; }

void Player::setName(const QString &name) { this->name = name; }

void Player::setAddr(const QString &addr) { this->addr = addr; }


int Player::calculatePoints()
{
    qDebug("Player::calculatePoints");
}



void Player::addCard(Card *card)
{
    cards.append(QSharedPointer<Card>(card));
}

void Player::blockTurn()
{
    turns_blocked++;
}
