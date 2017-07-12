#ifndef GAME_H
#define GAME_H

#include <QObject>

class Card;
class Deck;
class Player;

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

public:
    explicit Game(QObject *parent = 0);
    ~Game();

    GameStates getState();

    const QList<QSharedPointer<Player>> &getPlayers();
    QSharedPointer<Player> getActivePlayer();
    QSharedPointer<Player> getNextPlayer();

    Deck *getDeck();

signals:
    void playerJoined(Player *player);
    void playerLeft(Player *player);

    void gameStateChanged();
    void gameStarted();
    void newRoundStarted();

public slots:
    void finish();
    void newRound();

    void join(Player *player);
    void leave(Player *player);

    void start();

protected:
    Deck *deck;
    QList<QSharedPointer<Player>> players;
    GameStates state;
    int active;
};


#endif // GAME_H
