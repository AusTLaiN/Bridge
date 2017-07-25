#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "global.h"
#include "card.h"

namespace bridge_game {

class Player : public QObject, public Serializable
{
    Q_OBJECT

public:
    explicit Player(int m_id, QObject *parent = 0);

    const CardList &getCards();
    QString getName();
    QString getAddr();
    int getTurnsBlocked();

    int calculatePoints();
    int getScore();

    // Serializable interface

    virtual QJsonObject toJson() override;
    virtual void fromJson(const QJsonObject &json) override;

signals:
    void cardTaken(CardPtr card);
    void turnSkipped();
    void extraTurnGained();

public slots:
    void setName(const QString &m_name);
    void setAddr(const QString &m_addr);

    void takeCard(CardPtr card);
    void skipTurn();
    void takeExtraTurn();

    int addPoints();
    int addPoints(int points);

protected:
    CardList m_cards;
    QString m_name;
    QString m_addr;
    int m_turns_blocked;
    int m_score;

    int m_id;
};

} // bridge_game


#endif // PLAYER_H
