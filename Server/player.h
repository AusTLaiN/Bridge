#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "Server/Cards/card.h"

class Player : public QObject
{
    Q_OBJECT

public:
    typedef QList<QSharedPointer<Player>> PlayersList;

public:
    explicit Player(QObject *parent = 0);

    Card::CardList *getCards();
    QString getName();
    QString getAddr();
    int getTurnsBlocked();

    int calculatePoints();
    int getScore();

    QString toString();

signals:
    void turnBlocked();

public slots:
    void setName(const QString &name);
    void setAddr(const QString &addr);

    void addCard(Card *card);
    void addCard(QSharedPointer<Card> card);
    void skipTurn();

    int addPoints();
    int addPoints(int points);

protected:
    Card::CardList *cards;
    int turns_blocked;
    QString name;
    QString addr;
    int score;
};

#endif // PLAYER_H
