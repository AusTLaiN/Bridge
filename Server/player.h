#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QSharedPointer>

#include "Server/Cards/card.h"

class Player;

typedef QSharedPointer<Player> PlayerPtr;
typedef QList<PlayerPtr> PlayersList;

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = 0);

    const CardList &getCards();
    QString getName();
    QString getAddr();
    int getTurnsBlocked();

    int calculatePoints();
    int getScore();

    QString toString();

signals:
    void turnSkipped();
    void extraTurnGained();

public slots:
    void setName(const QString &name);
    void setAddr(const QString &addr);

    void takeCard(CardPtr card);
    void skipTurn();
    void takeExtraTurn();

    int addPoints();
    int addPoints(int points);

protected:
    CardList cards;
    QString name;
    QString addr;
    int turns_blocked;
    int score;
};

#endif // PLAYER_H
