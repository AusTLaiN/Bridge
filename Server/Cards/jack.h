#ifndef JACK_H
#define JACK_H

#include <QObject>

#include "global.h"
#include "card.h"

namespace bridge_game {

class Jack : public Card
{
    Q_OBJECT

public:
    explicit Jack(Suit suit, QObject *parent = 0);

public slots:
};

}

#endif // JACK_H
