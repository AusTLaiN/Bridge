#include "game.h"

Game::Game(QObject *parent) :
    QObject(parent),
    active(-1),
    state(NotStarted)
{
    /*connect(deck.data(), &Deck::noCardsLeft, [this]() {
        for (int i = 0; i < CARDS_TO_REMOVE; ++i)
        {
            deck->moveToGraveyard(deck->lastPlayed());
        }

        deck->restore();
        deck->shake();
    });*/
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
    emit newRoundStarted();
}

void Game::join(PlayerPtr player)
{
    players.append(player);
    emit playerJoined(player);
}

void Game::leave(PlayerPtr player)
{
    players.removeOne(player);
    emit playerLeft(player);
}

void Game::takeCard(PlayerPtr target)
{
    auto card = deck->takeCard();
    if (card == nullptr)
    {
        for (int i = 0; i < CARDS_TO_REMOVE; ++i)
        {
            deck->moveToGraveyard(deck->lastPlayed());
        }

        deck->restore();
        deck->shake();

        card = deck->takeCard();
    }

    target->takeCard(card);
    emit playerTakenCard(target, card);
}

void Game::finish()
{
    changeGameState(Finished);
}

void Game::start()
{
    changeGameState(InProgress);
}

void Game::pause()
{
    changeGameState(Paused);
}

void Game::changeGameState(Game::GameStates state)
{
    this->state = state;
    emit gameStateChanged(state);
}
