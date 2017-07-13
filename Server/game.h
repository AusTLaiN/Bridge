#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QSharedPointer>

#include "Server/deck.h"
#include "Server/player.h"

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
    PlayerPtr getActivePlayer();
    PlayerPtr getNextPlayer();

    DeckPtr getDeck();

signals:
    void playerJoined(PlayerPtr player);
    void playerLeft(PlayerPtr player);

    void playerTakenCard(PlayerPtr player, CardPtr card);
    void playerSkippedTurn(PlayerPtr player);
    void playerTakenExtraTurn(PlayerPtr player);

    void gameStateChanged(GameStates state);
    void gameStarted();
    void newRoundStarted();

public slots:
    void finish();
    void newRound();

    void join(PlayerPtr player);
    void leave(PlayerPtr player);

    void takeCard(PlayerPtr target);

    void start();
    void pause();

protected slots:
    void changeGameState(GameStates state);

protected:
    DeckPtr deck;
    PlayersList players;
    GameStates state;
    int active;
};


#endif // GAME_H
