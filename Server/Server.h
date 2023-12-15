#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QtCore>
#include <QtNetwork>
#include <QString>

namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();
signals:
    void receiveMsg(QByteArray);
    void receiveFile(const QString);

private slots:
    void newConnection();
    void disconnected();
    void readyRead();
    void sendMsg(const QString &data, QTcpSocket *senderSocket);
    void sendFile();

private:
    Ui::Server *ui;
    QTcpServer *server;
    QList<QTcpSocket*> sockets; // 수정된 부분
    QHash<QTcpSocket*, QByteArray*> buffers;
    bool send_flag = false;
    uint32_t cnt = 0;
};
#endif // SERVER_H

