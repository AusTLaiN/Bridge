#ifndef ACTIONREFILLDECK_H
#define ACTIONREFILLDECK_H

#include "abstractaction.h"

namespace bridge_game {

class ActionRefillDeck : public AbstractAction
{
public:
    ActionRefillDeck(Game *game, QObject *parent = nullptr);

public slots:
    virtual void execute() override;
};

}


#endif // ACTIONREFILLDECK_H
