#ifndef ACTIONGAMESTART_H
#define ACTIONGAMESTART_H

#include "abstractaction.h"

namespace bridge_game {

class ActionGameStart : public AbstractAction
{
public:
    ActionGameStart(Game *game, QObject *parent = nullptr);

public slots:
    virtual void execute() override;
};

}



#endif // ACTIONGAMESTART_H
