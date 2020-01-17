/*
** EPITECH PROJECT, 2019
** client
** File description:
** MyTcpSocket
*/

#include <iostream>
#include <cstring>
#include <QtWidgets/QMessageBox>

#include "../inc/MyTcpSocket.hpp"
#include "../inc/Client.hpp"
#include "../inc/request.hpp"
#include "../inc/Friend.hpp"

MyTcpSocket::MyTcpSocket(Client &client)
    : QObject(), m_client(client)
{

}

MyTcpSocket::~MyTcpSocket()
{

}

bool MyTcpSocket::do_connect(const std::string &pseudo, const std::string &passwd, const std::string &ip, const int &port)
{
    m_socket = new QTcpSocket;
    m_pseudo = pseudo;
    m_passwd = passwd;

    connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(m_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytes_written(qint64)));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(ready_read()));

    m_socket->connectToHost(QString(ip.data()), port);
    if (!m_socket->waitForConnected())
        return false;
    return true;
}

void MyTcpSocket::do_disconnect()
{
    m_socket->disconnectFromHost();
}

const QPointer<QTcpSocket> MyTcpSocket::get_socket()
{
    return m_socket;
}

void MyTcpSocket::connected()
{
    std::cout << "Connected !" << std::endl;
    request_t try_login;
    try_login.code = R_LOGIN;
    std::strcpy(try_login.data.login.username, m_pseudo.data());
    std::strcpy(try_login.data.login.password, m_passwd.data());
    m_client.do_write(try_login);
}

void MyTcpSocket::disconnected()
{
    std::cout << "Disconnected !" << std::endl;
    m_client.disconnected();
}

void MyTcpSocket::bytes_written(qint64 bytes)
{
    std::cout << "Written " << bytes << " bytes." << std::endl;
}

void MyTcpSocket::ready_read()
{
    request_t data;
    QPointer<Friend> friends;
    std::cout << "bytes available : " << m_socket->bytesAvailable() << std::endl;
    if (m_socket->bytesAvailable() < sizeof(request_t))
        return;
    std::memcpy(&data, m_socket->read(sizeof(request_t)), sizeof(request_t));

    std::cout << "data code : " << static_cast<int>(data.code) << std::endl;
    switch (data.code) {
        case R_NONE:
            break;
        case R_PLEASE_LOGIN:
            break;
        case R_UNDEFINED:
            break;
        case R_LOGIN:
            break;
        case R_SIGNUP:
            break;
        case R_LOGIN_SUCCESS:
            std::cout << "login success !!!" << std::endl;
            break;
        case R_SIGNUP_SUCCESS:
            std::cout << "signup success !!!" << std::endl;
            break;
        case R_LOGIN_FAILURE:
            m_client.do_disconnect();
            std::cout << "login failure !!!" << std::endl;
            break;
        case R_SIGNUP_FAILURE:
            m_client.do_disconnect();
            std::cout << "signup failure !!!" << std::endl;
            break;
        case R_ADD_FRIEND:
            break;
        case R_ACCEPT_FRIEND:
            break;
        case R_DENY_FRIEND:
            break;
        case R_SEND_MSG:
            break;
        case R_GET_ONLINE:
            break;
        case R_BEGIN_FRIEND:
            std::cout << "begin friend" << std::endl;
            m_client.reset_friends();
            break;
        case R_FRIEND_INFO:
            std::cout << data.data.friend_info.username << " ip " << data.data.friend_info.ip << " status " << data.data.friend_info.online << std::endl;
            friends = new Friend(m_client, data.data.friend_info.username, data.data.friend_info.ip, data.data.friend_info.online);
            m_client.set_friend(friends);
            break;
        case R_END_FRIEND:
            std::cout << "end friend" << std::endl;
            m_client.update_friends();
            break;
        case R_BAD_USERNAME:
            std::cout << "Bad username" << std::endl;
            break;
        case R_REICV_CALL:
            m_client.receive_call(data.data.call.username, data.data.call.ip, data.data.call.port);
            break;
    default:
        std::cout << "unknow" << std::endl;
        break;
    }
    if (m_socket->bytesAvailable())
        ready_read();
}