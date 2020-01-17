/*
** EPITECH PROJECT, 2019
** src
** File description:
** Friend
*/

#ifndef FRIEND_H_
#define FRIEND_H_

#include <QtCore/QPointer>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

#include "Client.hpp"

class Friend : public QWidget
{
Q_OBJECT

private:
    Client &m_client;
    QPointer<QPushButton> m_button;
    std::string m_pseudo;
    std::string &m_ip;
    bool m_is_connected;

public:
    Friend(Client &client, std::string pseudo, std::string ip="", bool is_connected=false);
    ~Friend();

    const QPointer<QPushButton> get_button();

public slots:
    void do_call();
};

#endif