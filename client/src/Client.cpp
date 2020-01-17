/*
** EPITECH PROJECT, 2019
** client
** File description:
** Client
*/

#include <iostream>
#include <cstring>

#include "../inc/Client.hpp"

Client::Client(QApplication &app)
    : m_app(app), m_wconnection(new WConnection(app, *this)), m_wserver(new WServer(app, *this)), m_tcp_socket(new MyTcpSocket(*this)), m_pseudo("")
{
    m_wconnection->show();
    m_wserver->show();
    m_wserver->set_visible(false); 
}

Client::~Client()
{

}

bool Client::do_connect(const std::string &pseudo, const std::string &passwd, const std::string &ip, const int &port)
{
    if (!m_tcp_socket->do_connect(pseudo, passwd, ip, port)) {
        std::cout << "Error : While connecting !" << std::endl;
        return false;
    }
    m_wserver->reset();
    m_wconnection->setVisible(false);
    m_wserver->set_visible(true);
    return true;
}

void Client::do_disconnect()
{
    m_tcp_socket->do_disconnect();
}

void Client::disconnected()
{
    m_wconnection->reset();
    m_wserver->set_visible(false);
    m_wconnection->setVisible(true);
}

void Client::reset_friends()
{
    m_wserver->reset_friends();
}

void Client::set_friend(QPointer<Friend> friends)
{
    m_wserver->set_friend(friends);
}

void Client::update_friends()
{
    m_wserver->show();
}

void Client::receive_call(const std::string &pseudo, const std::string &ip, int port)
{
    m_wserver->receive_call(pseudo, ip, port);
}

void Client::do_write(request_t &req)
{
    char *data = reinterpret_cast<char *>(&req);
    request_t requ;
    std::memcpy(&requ, data, sizeof(request_t));
    std::cout << "req code : " << (int)requ.code << std::endl;
    m_tcp_socket->get_socket()->write(data, sizeof(request_t));
}

const std::string &Client::get_pseudo()
{
    return m_pseudo;
}

void Client::set_pseudo(const std::string &pseudo)
{
    m_pseudo = pseudo;
}