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
    explicit Card(QObject *parent = 0);
    virtual ~Card() = 0;

    bool isPlayable();
    int getValue();
    QString getName();
    Suit getSuit();
    Rank getRank();

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

    virtual void action() = 0;

protected:
    void init();

protected:
    bool _playable;
    QString _name;
    int _value;
    Rank _rank;
    Suit _suit;
};

#endif // CARD_H
