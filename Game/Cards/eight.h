#ifndef EIGHT_H
#define EIGHT_H

#include <QObject>

#include "global.h"
#include "card.h"

namespace bridge_game {

class Eight : public Card
{
    Q_OBJECT

public:
    explicit Eight(Suit suit, QObject *parent = 0);

public slots:
    virtual void action(ActionArgs args) override;
};

}

#endif // EIGHT_H
