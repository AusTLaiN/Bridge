#ifndef ACTIONSETACTIVESUIT_H
#define ACTIONSETACTIVESUIT_H

#include "abstractaction.h"
#include "card.h"

namespace bridge_game {

class ActionSetActiveSuit : public AbstractAction
{
public:
    ActionSetActiveSuit(Game *game, Card::Suit suit, QObject *parent = nullptr);

public slots:
    virtual void execute() override;

protected:
    Card::Suit m_suit;
};

}


#endif // ACTIONSETACTIVESUIT_H
