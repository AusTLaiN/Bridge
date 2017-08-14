#ifndef GAMEOBJECTSMANAGER_H
#define GAMEOBJECTSMANAGER_H

#include "server.h"

namespace bridge_server {

class GameObjectsManager : public QObject
{
    Q_OBJECT
public:

    static GameObjectsManager& Instance()
    {
        static GameObjectsManager obj;
        return obj;
    }

    QList<uint> getPlayerIdListByGameId(uint gameId);
    bridge_game::GamePtr getGame(QWebSocket* ws);
    bridge_game::PlayerPtr getPlayer(QWebSocket* ws);

public slots:
    void createNewGame();
    void playerJoinToGame(uint gameId);
    void playerLeftGame();
    void playCard();

private:
    GameObjectsManager();
    GameObjectsManager(const GameObjectsManager&) = delete;
    GameObjectsManager& operator= (const GameObjectsManager&) = delete;
    ~GameObjectsManager();

    uint getGameId(QWebSocket* ws);
    uint getNextGameId();
    uint getPlayerId(QWebSocket* ws);
    uint getNextPlayerId();

    static uint m_playerIdCounter;
    static uint m_gameIdCounter;

    QMap<uint, QWebSocket *> m_playersInGame;
    QMap<uint, bridge_game::GamePtr> m_games;
};

uint GameObjectsManager::m_playerIdCounter = 0;
uint GameObjectsManager::m_gameIdCounter = 0;

} // bridge_server

#endif // GAMEOBJECTSMANAGER_H
