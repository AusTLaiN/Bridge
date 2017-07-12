#ifndef SIX_H
#define SIX_H

#include <QObject>

#include "card.h"

class Six : public Card
{
    Q_OBJECT

public:
    explicit Six(Card::Suit suit, QObject *parent = 0);

public slots:
};

#endif // SIX_H
