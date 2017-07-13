#include "game.h"

Game::Game(QObject *parent) :
    QObject(parent),
    active(-1),
    state(NotStarted)
{
    connect(deck.data(), &Deck::noCardsLeft, [this]() {
        for (int i = 0; i < CARDS_TO_REMOVE; ++i)
        {
            deck->moveToGraveyard(deck->lastPlayed());
        }

        deck->restore();
        deck->shake();
    });
}

Game::~Game()
{
}

Game::GameStates Game::getState() { return state; }

const PlayersList &Game::getPlayers() { return players; }

PlayerPtr Game::getActivePlayer()
{
    return players[active];
}

PlayerPtr Game::getNextPlayer()
{
    if (players[active] == players.last())
        return players.first();
    return players[active + 1];
}

DeckPtr Game::getDeck()
{
    return deck;
}

void Game::newRound()
{

}

void Game::join(PlayerPtr player)
{

}

void Game::leave(PlayerPtr player)
{

}

void Game::finish()
{

}

void Game::start()
{

}
