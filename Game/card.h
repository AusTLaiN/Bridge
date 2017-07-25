#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QDebug>

#include "global.h"
#include "actionargs.h"

namespace bridge_game {

class Card : public QObject, public Serializable
{
    Q_OBJECT

public:
    enum Suit {
        Clubs           = 1,
        Diamonds        = 2,
        Hearts          = 3,
        Spades          = 4,

        UndefinedSuit   = 100000,
        AnySuit         = 100001
    };
    Q_ENUM(Suit)

    enum Rank {
        Six             = 6,
        Seven           = 7,
        Eight           = 8,
        Nine            = 9,
        Ten             = 10,
        Jack            = 11,
        Queen           = 12,
        King            = 13,
        Ace             = 14,

        UndefinedRank   = 200000,
        AnyRank         = 200001
    };
    Q_ENUM(Rank)

    static int cardValue(Rank card_rank, bridge_game::Card::Suit suit);
    static Rank cardRank(int numeric_rank);
    static QString toString(Rank rank);
    static QString toString(Suit suit);

public:
    explicit Card(Rank rank, Suit suit, QObject *parent = 0);
    virtual ~Card() = 0;

    bool isPlayable();
    int getValue();
    Suit getSuit();
    Rank getRank();

    // Serializable interface

    virtual QJsonObject toJson() override;
    virtual void fromJson(const QJsonObject &json) override;

signals:
    void playableChanged(bool flag);

public slots:
    void setPlayable(bool playable);
    /*void setValue(int value);
    void setSuit(Suit suit);
    void setRank(Rank rank);*/

    virtual void action(ActionArgs args);

protected:
    bool m_playable;
    int m_value;
    Rank m_rank;
    Suit m_suit;
};

} // bridge_game

#endif // CARD_H
