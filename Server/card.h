#ifndef CARD_H
#define CARD_H

#include <QObject>

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

    // Game value = enum value / 1000
    // Example : King = 10013 / 1000 = 10 points
    // Card rank = last 2 numbers
    // Example : Jack = 20011 % 100 = 11 ( Jack comes after 10 )
    enum Rank {
        Six = 106,
        Seven = 107,
        Eight = 108,
        Nine = 109,
        Ten = 10010,
        Jack = 20011,
        Queen = 10012,
        King = 10013,
        Ace = 15014
    };
    Q_ENUM(Rank)

    typedef QList<QSharedPointer<Card>> CardList;

public:
    explicit Card(QObject *parent = 0);
    virtual ~Card() = 0;

    bool isPlayable();
    int getValue();
    QString getName();
    Suit getSuit();
    Rank getRank();

    virtual void action() = 0;

signals:
    void playableChanged(bool flag);
    /*void nameChanged(const QString &name);
    void valueChanged(int value);
    void suitChanged(Suit suit);
    void rankChanged(Rank rank);*/

public slots:
    void setPlayable(bool playable);
    void setValue(int value);
    void setName(const QString &name);
    void setSuit(Suit suit);
    void setRank(Rank rank);

protected:
    bool _playable;
    QString _name;
    int _value;
    Rank _rank;
    Suit _suit;
};

#endif // CARD_H
