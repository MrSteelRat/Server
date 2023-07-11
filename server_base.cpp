#include "server_base.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class ChatServer : public QTcpServer {

public:
    explicit ChatServer(QObject* parent = nullptr) : QTcpServer(parent) {}

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket* clientSocket = new QTcpSocket(this);
        clientSocket->setSocketDescriptor(socketDescriptor);

        connect(clientSocket, &QTcpSocket::readyRead, this, [=]() {
            onReadyRead(clientSocket);
        });

        connect(clientSocket, &QTcpSocket::disconnected, this, [=]() {
            onDisconnected(clientSocket);
        });

        clientSockets.append(clientSocket);
        emit clientConnected(clientSocket->peerAddress().toString());

        qDebug() << "Client connected:" << clientSocket->peerAddress().toString();
    }

private slots:
    void onReadyRead(QTcpSocket* clientSocket) {
        QByteArray data = clientSocket->readAll();
        emit messageReceived(clientSocket->peerAddress().toString(), data);
    }

    void onDisconnected(QTcpSocket* clientSocket) {
        clientSockets.removeOne(clientSocket);
        emit clientDisconnected(clientSocket->peerAddress().toString());

        qDebug() << "Client disconnected:" << clientSocket->peerAddress().toString();

        clientSocket->deleteLater();
    }

signals:
    void messageReceived(const QString& sender, const QByteArray& message);
    void clientConnected(const QString& clientAddress);
    void clientDisconnected(const QString& clientAddress);

private:
    QList<QTcpSocket*> clientSockets;
};
