#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QtCore>
#include <QtNetwork>
#include "ui_Client.h"

namespace Ui {
class Client;
}

class Client : public QMainWindow
{ 
    Q_OBJECT
public:
    explicit Client(const QString &username, QWidget *parent = nullptr);
    ~Client();

signals:
    void sendFile();
    
    public slots:
        bool connectToHost(QString host);
        bool sendMsg(QByteArray data);
        void sendFile(const QString &filePath);
    
    private slots:
        void on_sendButton_clicked();
        void on_pushButtonSendFile_clicked();
        void on_pushButtonReceiveFile_clicked();
    
    private slots:
        void readyRead();
        
    private slots:
        void receiveMsg(QByteArray data);
        void receiveFile(const QString &filePath);

    private:
        Ui::Client *ui;
        QString username;
        QTcpSocket *socket;
        QByteArray data;
        bool fd_flag = false;
        bool send_flag = false;
};

#endif
