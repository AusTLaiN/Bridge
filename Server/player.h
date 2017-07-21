#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "global.h"
#include "Cards/card.h"

namespace bridge_game {

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
    void cardTaken(CardPtr card);
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

} // bridge_game


#endif // PLAYER_H
