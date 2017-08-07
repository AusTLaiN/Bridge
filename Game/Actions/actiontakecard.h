#ifndef ACTIONTAKECARD_H
#define ACTIONTAKECARD_H

#include "abstractaction.h"

namespace bridge_game {

class ActionTakeCard : public AbstractAction
{
public:
    ActionTakeCard(Game *game, QObject *parent = nullptr);

public slots:
    virtual void execute() override;
};

}


#endif // ACTIONTAKECARD_H
