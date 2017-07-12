#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "Server/card.h"

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = 0);

    Card::CardList getCards();
    QString getName();
    QString getAddr();

signals:

public slots:
    void addCard(Card* card);
    void setName(const QString &name);
    void setAddr(const QString &addr);

protected:
    Card::CardList cards;
};

#endif // PLAYER_H
