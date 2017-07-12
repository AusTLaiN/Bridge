#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include <QObject>

#include "Server/game.h"
#include "Server/player.h"
#include "Server/deck.h"

class Player;
class Game;
class Deck;

class AbstractAction : public QObject
{
    Q_OBJECT

public:
    explicit AbstractAction(QObject *parent = 0);
    virtual ~AbstractAction() = 0;

signals:
    void done();

public slots:
    virtual void proceed(Game* game, Player* made_by, Deck* deck) = 0;
};

#endif // ABSTRACTACTION_H
