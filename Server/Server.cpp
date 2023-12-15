#include "Server.h"
#include "ui_Server.h"

Server::Server(QWidget *parent) : QMainWindow(parent), ui(new Ui::Server)
{
    ui->setupUi(this);
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    
    QString socket_data;
    socket_data.sprintf("Listening: %s\n", server->listen(QHostAddress::Any, 8888) ? "true" : "false");
    ui->textEdit->insertPlainText(socket_data);
}

Server::~Server()
{
    delete ui;
}

void Server::newConnection()
{
    while (server->hasPendingConnections()) {
        QTcpSocket *socket = server->nextPendingConnection();
        socket->setObjectName(QString::number(cnt));
        ui->textEdit->insertPlainText("Connected from " + QString::number(cnt++) + "\r\n");
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        connect(socket, SIGNAL(sendFile()), this, SLOT(sendFile()));
        sockets.append(socket);
        QByteArray *buffer = new QByteArray();
        buffers.insert(socket, buffer);
    }
}

void Server::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    socket->deleteLater();
    delete buffer;
    sockets.removeAll(socket);
}

void Server::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    while (socket->bytesAvailable() > 0) {
        buffer->append(socket->readAll());
        ui->textEdit->insertPlainText(QString(buffer->data()) + "\r\n");
        sendMsg((QString(buffer->data())), socket);

        qint32 size = buffer->size();
        QByteArray data = buffer->mid(0, size);
        buffer->remove(0, size);
        emit receiveMsg(data);
    }
}

void Server::sendMsg(const QString &data, QTcpSocket *senderSocket)
{
    foreach (QTcpSocket *socket, sockets) {
        if (socket != senderSocket) {
            socket->write(data.toUtf8());
            socket->waitForBytesWritten();
        }
    }
}

void Server::sendFile()
{
    QTcpSocket *senderSocket = static_cast<QTcpSocket*>(sender());


    QByteArray fileData = senderSocket->readAll();

    // Broadcast the file data to all clients
    for (QTcpSocket *socket : sockets) {
        if (socket != senderSocket) {
            socket->write(fileData);
            socket->waitForBytesWritten();
        }
    }
}

int main(int argc, char **argv)
{
    QApplication app(argc,argv);
    Server *window = new Server();

    window->show();
    
    return app.exec();
}

