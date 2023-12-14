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
    
    public slots:
        bool connectToHost(QString host);
        bool sendMsg(QByteArray data);
    
    private slots:
        void on_sendButton_clicked();
    
    private slots:
        void readyRead();
        
    private slots:
        void receiveMsg(QByteArray data);

    private:
        Ui::Client *ui;
        QString username;
        QTcpSocket *socket;
        bool fd_flag = false;
        bool send_flag = false;
};

#endif
