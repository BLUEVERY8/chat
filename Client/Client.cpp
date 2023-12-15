#include "Client.h"
#include "ui_Client.h"
#include <QFileDialog>

Client::Client(const QString &username, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client),
    username(username)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    fd_flag = connectToHost("127.0.0.1");
    QByteArray data;

    if (!fd_flag)
        ui->textEdit->insertPlainText("Socket connect fail\n");
}

Client::~Client()
{
    delete ui;
}

bool Client::connectToHost(QString host)
{
    socket->connectToHost(host, 8888);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(receiveFile()), this, SLOT(receiveFile()));
    return socket->waitForConnected();
}

bool Client::sendMsg(QByteArray data)
{
    if(socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(data);
        ui->textEdit->insertPlainText(QString(data) + "\r\n");
        return socket->waitForBytesWritten();
    }
    else {
        return false;
    }
}

void Client::on_sendButton_clicked()
{
    if (fd_flag) {
        QString sendData;
        sendData = ui->lineEdit->text();
        send_flag = sendMsg((username + ": " + sendData).toStdString().c_str());
        if (!send_flag)
            ui->textEdit->insertPlainText("Socket send fail\n");
            
        ui->lineEdit->clear();
    }
}

void Client::sendFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Error: Unable to open file for reading";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    socket->write(fileData);
    emit sendFile();

}

void Client::on_pushButtonSendFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select a file to send");
    if (!filePath.isEmpty()) {
        sendFile(filePath);
    }
}

void Client::on_pushButtonReceiveFile_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save received file");
    if (!filePath.isEmpty()) {
        receiveFile(filePath);
    }
}

void Client::readyRead()
{
    while (socket->bytesAvailable() > 0) {
        data = socket->readAll();
        ui->textEdit->insertPlainText(QString(data) + "\r\n");
    }
}

void Client::receiveMsg(QByteArray data)
{
    ui->textEdit->insertPlainText(QString(data) + "\r\n");
}

void Client::receiveFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Error: Unable to open file for writing";
        return;
    }
    
    QString textContent = ui->textEdit->toPlainText();
    
    QTextStream outStream(&file);
    outStream << textContent;
    
    file.close();
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        qDebug() << "Usage: ./Client <username>";
        return 1;
    }

    QApplication app(argc, argv);
    QString username = QString(argv[1]);
    Client *window = new Client(username);

    window->show();

    return app.exec();
}

