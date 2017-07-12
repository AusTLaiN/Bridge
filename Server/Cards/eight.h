#ifndef EIGHT_H
#define EIGHT_H

#include <QObject>

#include "card.h"

class Eight : public Card
{
    Q_OBJECT

public:
    explicit Eight(Suit suit, QObject *parent = 0);

public slots:
    virtual void action(Game *game) override;
};

#endif // EIGHT_H
