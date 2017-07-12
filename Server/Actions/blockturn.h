#ifndef BLOCKTURN_H
#define BLOCKTURN_H

#include <QObject>

#include "abstractaction.h"

class BlockTurn : public AbstractAction
{
    Q_OBJECT

public:
    explicit BlockTurn(QObject *parent = 0);

public slots:
    virtual void proceed(Game *game, Player *made_by) override;
};

#endif // BLOCKTURN_H
