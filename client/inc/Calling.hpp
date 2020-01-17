/*
** EPITECH PROJECT, 2019
** src
** File description:
** Calling
*/

#ifndef CALLING_H_
#define CALLING_H_

#include <QtCore/QPointer>
#include <QtWidgets/QDialog>
#include <QtNetwork/QUdpSocket>

#include "Client.hpp"
#include "Record.hpp"

class Calling : public QDialog
{
private:
    Client &m_client;
    QPointer<QUdpSocket> m_socket;
    std::string &m_pseudo;
    bool m_connected;
    Record m_rec;

public:
    Calling(Client &client, QWidget *parent, std::string pseudo);
    ~Calling();

    void call();
    void ready_read();
    void connected();
    void disconnected();
    void stop();
};

#endif