#ifndef SERVER_H
#define SERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(quint16 port, QObject *parent = Q_NULLPTR);
    virtual ~Server();

private Q_SLOTS:
    void onNewConnection();
    void processMessage(QString message);
    void socketDisconnected();

private:
    QWebSocketServer * m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};

#endif // SERVER_H
