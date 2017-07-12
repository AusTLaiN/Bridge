#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include <QObject>

#include "Server/game.h"
#include "Server/player.h"

class Player;
class Game;

class AbstractAction : public QObject
{
    Q_OBJECT

public:
    explicit AbstractAction(QObject *parent = 0);
    virtual ~AbstractAction() = 0;

signals:
    void done();

public slots:
    virtual void proceed(Game *game, Player *made_by) = 0;
};

#endif // ABSTRACTACTION_H
