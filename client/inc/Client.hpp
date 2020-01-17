/*
** EPITECH PROJECT, 2019
** client
** File description:
** Client
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include <QtNetwork/QTcpSocket>

#include "WConnection.hpp"
#include "WServer.hpp"
#include "MyTcpSocket.hpp"
#include "request.hpp"

class Client
{
private:
    QApplication &m_app;
    QPointer<WConnection> m_wconnection;
    QPointer<WServer> m_wserver;
    QPointer<MyTcpSocket> m_tcp_socket;
    std::string m_pseudo;

public:
    Client(QApplication &app);
    ~Client();

    bool do_connect(const std::string &pseudo, const std::string &passwd, const std::string &ip, const int &port);
    void do_disconnect();
    void do_write(request_t &req);
    void disconnected();
    void reset_friends();
    void set_friend(QPointer<Friend> friends);
    void update_friends();
    void receive_call(const std::string &pseudo, const std::string &ip, int port);

    const std::string &get_pseudo();
    void set_pseudo(const std::string &pseudo);
};

#endif