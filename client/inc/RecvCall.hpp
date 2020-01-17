/*
** EPITECH PROJECT, 2019
** src
** File description:
** RecvCall
*/

#ifndef RECVCALL_H_
#define RECVCALL_H_

#include <QtCore/QPointer>
#include <QtWidgets/QDialog>
#include <QtNetwork/QUdpSocket>

#include "Client.hpp"
#include "Record.hpp"

class RecvCall : public QDialog
{
private:
    Client &m_client;
    QPointer<QUdpSocket> m_socket;
    std::string m_ip;
    int m_port;
    Record m_rec;

public:
    RecvCall(Client &client, QWidget *parent, std::string ip, int port);
    ~RecvCall();

    void call();
    void ready_read();
    void connected();
    void disconnected();
    void stop();
};

#endif