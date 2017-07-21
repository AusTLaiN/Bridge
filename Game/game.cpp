#include "game.h"

using namespace bridge_game;

Game::Game(QObject *parent) :
    QObject(parent),
    active(-1),
    state(NotStarted),
    current_suit(Card::AnySuit)
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

PlayerPtr Game::getPlayer(int index)
{
    if (index < 0)
        qDebug("Game::getPlayer: index < 0");
    else if (index > players.count())
        qDebug("Game::getPlayer: index > players count");
    else
    {
        return players[index];
    }
}

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
    current_suit = Card::AnySuit;
    active = 0;

    deck.reset(new Deck);
    deck->shuffle();

    changeGameState(InProgress);
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
        deck->shuffle();

        card = deck->takeCard();
    }

    target->takeCard(card);
    emit playerTakenCard(target, card);
}

void Game::skipTurn(PlayerPtr target)
{
    target->skipTurn();
    emit playerSkippedTurn(target);
}

void Game::extraTurn(PlayerPtr target)
{
    target->takeExtraTurn();
    emit playerTakenExtraTurn(target);
}

void Game::setActiveSuit(Card::Suit suit)
{
    current_suit = suit;
    emit activeSuitChanged(suit);
}

void Game::setActivePlayer(int index)
{
    if (index < 0)
        qDebug("Game::setActivePlayer: index < 0");
    else if (index > players.count())
        qDebug("Game::setActivePlayer: index > players count");
    else
    {
        active = index;
        emit activePlayerChanged(index);
        emit activePlayerChanged(players[index]);
    }
}

void Game::setActivePlayer(PlayerPtr player)
{
    if (players.contains(player))
    {
        auto index = players.indexOf(player);
        setActivePlayer(index);
    }
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
