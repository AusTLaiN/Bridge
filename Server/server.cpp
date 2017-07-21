#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>

#include "Server/server.h"

QT_USE_NAMESPACE

Server::Server(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(Q_NULLPTR)
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Server"),
                                              QWebSocketServer::NonSecureMode,
                                              this);
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server listening on port " << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &Server::onNewConnection);
    }
}

Server::~Server()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void Server::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);
    qDebug() << "Client" << pSocket << "connected";
    m_clients << pSocket;
}

void Server::processMessage(QString message)
{
    qDebug() << message;
    // QWebSocket *pSender = qobject_cast<QWebSocket *>(sender()); // getting sender
    for (QWebSocket *pClient : qAsConst(m_clients)) // send to all registered users
    {
        pClient->sendTextMessage(message);
    }
}

void Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        qDebug() << "Client" << pClient << "disconnected";
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
