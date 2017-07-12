#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "Server/Cards/card.h"

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = 0);

    const Card::CardList& getCards();
    QString getName();
    QString getAddr();
    int getTurnsBlocked();

    int calculatePoints();

signals:
    void turnBlocked();

public slots:
    void setName(const QString &name);
    void setAddr(const QString &addr);

    void addCard(Card* card);
    void blockTurn();

protected:
    Card::CardList cards;
    int turns_blocked;
    QString name;
    QString addr;
};

#endif // PLAYER_H
