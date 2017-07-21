#ifndef GAME_H
#define GAME_H

#include <QObject>

#include "global.h"
#include "deck.h"
#include "player.h"

namespace bridge_game {

class Game : public QObject
{
    Q_OBJECT

public:
    enum GameStates {
        NotStarted,
        InProgress,
        Finished,
        Paused
    };

    static const int WIN_SCORE = 125;
    static const int PLAYERS_LIMIT = 5;
    static const int TURN_TIME_LIMIT = 90 * 1000;
    static const int CARDS_TO_REMOVE = 2;

public:
    explicit Game(QObject *parent = 0);
    ~Game();

    GameStates getState();

    const PlayersList &getPlayers();
    PlayerPtr getPlayer(int index);
    PlayerPtr getActivePlayer();
    PlayerPtr getNextPlayer();

    DeckPtr getDeck();

signals:
    void playerJoined(PlayerPtr player);
    void playerLeft(PlayerPtr player);

    void playerTakenCard(PlayerPtr player, CardPtr card);
    void playerSkippedTurn(PlayerPtr player);
    void playerTakenExtraTurn(PlayerPtr player);
    void activeSuitChanged(Card::Suit suit);

    void activePlayerChanged(PlayerPtr player);
    void activePlayerChanged(int index);

    void gameStateChanged(GameStates state);
    void gameStarted();
    void newRoundStarted();

public slots:
    void finish();
    void newRound();

    void join(PlayerPtr player);
    void leave(PlayerPtr player);

    void takeCard(PlayerPtr target);
    void skipTurn(PlayerPtr target);
    void extraTurn(PlayerPtr target);
    void setActiveSuit(Card::Suit suit);

    void setActivePlayer(int index);
    void setActivePlayer(PlayerPtr player);

    void start();
    void pause();

protected slots:
    void changeGameState(GameStates state);

protected:
    DeckPtr deck;
    PlayersList players;
    GameStates state;
    int active;
    Card::Suit current_suit;
};

} // bridge_game


#endif // GAME_H
