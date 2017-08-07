#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>

#include "Server/server.h"
#include "player.h"
#include "game.h"
#include "global.h"

QT_USE_NAMESPACE

using namespace bridge_game;
using namespace bridge_server;

Server::Server(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(Q_NULLPTR)//,
    //m_cmd()
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Server"),
                                              QWebSocketServer::NonSecureMode,
                                              this);
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "\nServer listening on port " << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &Server::onNewConnection);
    }
}

uint Server::m_playerIdCounter = 0;
uint Server::m_gameIdCounter = 0;

Server::~Server()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_players.begin(), m_players.end());
}

void Server::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);

    qDebug() << "Client" << pSocket << "connected";
    m_playersOutOfGame << pSocket;
}

void Server::processMessage(QString message)
{
    qDebug() << message;
    QWebSocket* pSender = qobject_cast<QWebSocket*>(sender()); // getting sender
    /*for (QWebSocket* pClient : qAsConst(m_playersOutOfGame))   // send to all registered users
    {
        pClient->sendTextMessage(message);
    }*/

    // ?.......
    Command cmd = Command(Command::ACTION::GamesInfoRequest); //
    switch(cmd.getAction())
    {
        case Command::ACTION::GamesInfoRequest:
        {
            char html[] = "<ul><li>test1</li><li>test2</li></ul>";
            pSender->sendTextMessage(html);
        }
            break;
        case Command::ACTION::CreateGameRequest:
        {       
            // Get IDs
            m_gameIdCounter++;
            m_playerIdCounter++;
            // New game creation
            GamePtr game = GamePtr(new Game(m_gameIdCounter));
            m_games[m_gameIdCounter] = game;

            // Saving callback channel by playerId
            m_players[m_playerIdCounter] = pSender;
            // Saving link - playerId => gameId
            m_PlayersGamesLink[m_playerIdCounter] = m_gameIdCounter;

            PlayerPtr player = PlayerPtr(new Player(m_playerIdCounter));
            m_games[m_PlayersGamesLink[player->getId()]]->join(player);

            m_playersOutOfGame.removeAll(pSender);
        }
            break;
        case Command::ACTION::JoinToGameRequest:
        {

        }
            break;
        case Command::ACTION::LeaveGameRequest:
            break;
    }
}

// TODO: to delete - All work must be throw processMessage
void Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        qDebug() << "Client" << pClient << "disconnected";
        m_playersOutOfGame.removeAll(pClient);
        pClient->deleteLater();
    }
}

void Server::sendCommandList()
{

}

uint Server::getGameIdByPlayerId(uint PlayerId)
{
    return m_PlayersGamesLink[PlayerId];
}
