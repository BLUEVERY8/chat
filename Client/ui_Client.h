/********************************************************************************
** Form generated from reading UI file 'Client.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QPushButton *sendButton;
    QPushButton *pushButtonSendFile;
    QPushButton *pushButtonReceiveFile;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(729, 507);
        Client->setMinimumSize(QSize(400, 300));
        centralwidget = new QWidget(Client);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setEnabled(true);
        textEdit->setGeometry(QRect(20, 10, 691, 371));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 400, 551, 25));
        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(600, 400, 111, 25));
        sendButton->setLocale(QLocale(QLocale::Korean, QLocale::SouthKorea));
        pushButtonSendFile = new QPushButton(centralwidget);
        pushButtonSendFile->setObjectName(QString::fromUtf8("pushButtonSendFile"));
        pushButtonSendFile->setGeometry(QRect(20, 430, 89, 25));
        pushButtonReceiveFile = new QPushButton(centralwidget);
        pushButtonReceiveFile->setObjectName(QString::fromUtf8("pushButtonReceiveFile"));
        pushButtonReceiveFile->setGeometry(QRect(120, 430, 89, 25));
        Client->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Client);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 729, 28));
        Client->setMenuBar(menubar);
        statusbar = new QStatusBar(Client);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Client->setStatusBar(statusbar);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "\355\201\264\353\235\274\354\235\264\354\226\270\355\212\270", nullptr));
        sendButton->setText(QCoreApplication::translate("Client", "\354\240\204\354\206\241", nullptr));
        pushButtonSendFile->setText(QCoreApplication::translate("Client", "\355\214\214\354\235\274 \354\240\204\354\206\241", nullptr));
        pushButtonReceiveFile->setText(QCoreApplication::translate("Client", "\355\214\214\354\235\274 \354\240\200\354\236\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
