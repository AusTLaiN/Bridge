#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QSharedPointer>
#include <QDebug>

class Game;

class Card : public QObject
{
    Q_OBJECT

public:
    enum Suit {
        Clubs = 1,
        Diamonds,
        Hearts,
        Spades
    };
    Q_ENUM(Suit)

    enum Rank {
        Six = 6,
        Seven = 7,
        Eight = 8,
        Nine = 9,
        Ten = 10,
        Jack = 11,
        Queen = 12,
        King = 13,
        Ace = 14
    };
    Q_ENUM(Rank)

    typedef QList<QSharedPointer<Card>> CardList;
    typedef QList<QScopedPointer<Card>> CardListUnique;

    static int cardValue(Rank card_rank);
    static Rank cardRank(int numeric_rank);
    static QString cardName(Rank card_rank, Suit card_suit);

public:
    explicit Card(Rank rank, Suit suit, QObject *parent = 0);
    virtual ~Card() = 0;

    bool isPlayable();
    int getValue();
    Suit getSuit();
    Rank getRank();

    virtual QString toString();

signals:
    void playableChanged(bool flag);

public slots:
    void setPlayable(bool playable);
    void setValue(int value);
    void setSuit(Suit suit);
    void setRank(Rank rank);

    virtual void action(Game* game);

protected:
    bool _playable;
    int _value;
    Rank _rank;
    Suit _suit;
};

#endif // CARD_H
