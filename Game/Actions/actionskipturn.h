#ifndef ACTIONSKIPTURN_H
#define ACTIONSKIPTURN_H

#include "abstractaction.h"

namespace bridge_game {

class ActionSkipTurn : public AbstractAction
{
public:
    ActionSkipTurn(Game *game, QObject *parent = nullptr);

public slots:
    virtual void execute() override;
};


}


#endif // ACTIONSKIPTURN_H
