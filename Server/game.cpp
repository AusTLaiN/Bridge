#include "game.h"

#include "Server/deck.h"
#include "Server/player.h"

Game::Game(QObject *parent) :
    QObject(parent),
    active(-1),
    deck(new Deck),
    state(NotStarted)
{

}

Game::~Game()
{
    delete deck;
}

Game::GameStates Game::getState() { return state; }

const QList<QSharedPointer<Player> > &Game::getPlayers() { return players; }

QSharedPointer<Player> Game::getActivePlayer()
{
    return players[active];
}

QSharedPointer<Player> Game::getNextPlayer()
{
    if (players[active] == players.last())
        return players.first();
    return players[active + 1];
}

Deck *Game::getDeck()
{
    return deck;
}

void Game::newRound()
{

}

void Game::join(Player *player)
{

}

void Game::leave(Player *player)
{

}

void Game::finish()
{

}

void Game::start()
{

}
