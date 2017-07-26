#ifndef GAME_H
#define GAME_H

#include <QObject>

#include "global.h"
#include "deck.h"
#include "player.h"

namespace bridge_game {

class Game : public QObject, public Serializable
{
    Q_OBJECT

public:
    enum GameStates {
        NotStarted,
        InProgress,
        Finished,
        Paused
    };
    Q_ENUM(GameStates)

    static QString toString(GameStates state);

    static const int WIN_SCORE = 125;
    static const int PLAYERS_LIMIT = 5;
    static const int TURN_TIME_LIMIT = 90 * 1000;
    static const int CARDS_TO_REMOVE = 2;

public:
    explicit Game(int id, QObject *parent = 0);
    ~Game();

    GameStates getState();

    const PlayersList& getPlayers();
    PlayerPtr getPlayer(int index);
    PlayerPtr getPlayerById(int id);
    PlayerPtr getActivePlayer();
    PlayerPtr getNextPlayer();

    DeckPtr getDeck();

    int getId();

    // Serializable interface

    virtual QJsonObject toJson() override;
    virtual void fromJson(const QJsonObject &json) override;

signals:
    void playerJoined(PlayerPtr player);
    void playerLeft(PlayerPtr player);

    void playerTakenCard(PlayerPtr player, CardPtr card);
    void playerSkippedTurn(PlayerPtr player);
    void playerTakenExtraTurn(PlayerPtr player);
    void activeSuitChanged(Card::Suit suit);

    void activePlayerChanged(PlayerPtr player);
    void activePlayerChanged(int index);

    void gameStateChanged(GameStates m_state);
    void gameStarted();
    void newRoundStarted();

    void errorOccured(const QString &message);

public slots:
    void finish();
    void newRound();

    void join(PlayerPtr player);
    void leave(PlayerPtr player);

    void takeCard(PlayerPtr target);
    void takeCards(PlayerPtr target, quint32 amount);
    void skipTurn(PlayerPtr target);
    void extraTurn(PlayerPtr target);
    void setActiveSuit(Card::Suit suit);

    void setActivePlayer(int index);
    void setActivePlayer(PlayerPtr player);

    void start();
    void pause();

protected slots:
    void changeGameState(GameStates m_state);
    void handleError(const QString &message);

protected:
    DeckPtr m_deck;
    PlayersList m_players;

    GameStates m_state;
    int m_id;

    int m_active_player;
    Card::Suit m_active_suit;
};

} // bridge_game


#endif // GAME_H
