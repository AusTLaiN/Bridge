#ifndef SEVEN_H
#define SEVEN_H

#include <QObject>

#include "card.h"

class Seven : public Card
{
    Q_OBJECT

public:
    explicit Seven(Suit suit, QObject *parent = 0);

public slots:
};

#endif // SEVEN_H
