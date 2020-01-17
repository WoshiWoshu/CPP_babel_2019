/*
** EPITECH PROJECT, 2019
** client
** File description:
** MyTcpSocket
*/

#ifndef MYTCPSOCKET_H_
#define MYTCPSOCKET_H_

#include <string>
#include <QtCore/QPointer>
#include <QtCore/QObject>
#include <QtNetwork/QTcpSocket>

class Client;

class MyTcpSocket : public QObject
{
Q_OBJECT

private:
    QPointer<QTcpSocket> m_socket;
    Client &m_client;
    std::string m_pseudo;
    std::string m_passwd;

public:
    MyTcpSocket(Client &client);
    ~MyTcpSocket();

    bool do_connect(const std::string &pseudo, const std::string &passwd, const std::string &ip, const int &port);
    void do_disconnect();
    const QPointer<QTcpSocket> get_socket();

public slots:
    void connected();
    void disconnected();
    void bytes_written(qint64 bytes);
    void ready_read();
};

#endif