#ifndef SERVER_H
#define SERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QMap>

#include "global.h"
#include "message.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

namespace bridge_server {

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(quint16 port, QObject *parent = Q_NULLPTR);
    virtual ~Server();

    void sendCommandList();
    bool initNewGame();

private Q_SLOTS:
    void onNewConnection();
    void processMessage(QString message);
    void socketDisconnected();
    uint getGameIdByPlayerId(uint PlayerId);
private:
    bool waitAnswerFlag;

    static uint m_playerIdCounter;
    static uint m_gameIdCounter;

    QWebSocketServer * m_pWebSocketServer;
    QList<QWebSocket *> m_playersOutOfGame;
    QMap<uint, QWebSocket *> m_players;
    QMap<uint, uint> m_PlayersGamesLink;
    QMap<uint, bridge_game::GamePtr> m_games;
};

}
#endif // SERVER_H
