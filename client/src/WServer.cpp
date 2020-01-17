/*
** EPITECH PROJECT, 2019
** client
** File description:
** WServer
*/

#include <iostream>
#include <cstring>
#include <QtCore/QPointer>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>

#include "../inc/WServer.hpp"
#include "../inc/Client.hpp"
#include "../inc/request.hpp"
#include "../inc/Friend.hpp"
#include "../inc/RecvCall.hpp"

WServer::WServer(QApplication &app, Client &client)
    : QWidget(), m_app(app), m_client(client), m_active(false)
{
    server_window();
}

WServer::~WServer()
{

}

void WServer::server_window()
{
    m_add_pseudo = new QLineEdit;
    m_add_pseudo->setMaxLength(UNAME_SIZE);

    QPointer<QPushButton> m_button_add_friend = new QPushButton("Add Friend");
    QWidget::connect(m_button_add_friend, SIGNAL(clicked()), this, SLOT(add_friend()));
    QPointer<QPushButton> button_disconnect = new QPushButton("Disconnect");
    QWidget::connect(button_disconnect, SIGNAL(clicked()), this, SLOT(do_disconnect()));

    m_friends_layout = new QVBoxLayout;

    m_main_layout = new QVBoxLayout;
    m_main_layout->addWidget(m_add_pseudo);
    m_main_layout->addWidget(m_button_add_friend);
    m_main_layout->addLayout(m_friends_layout);
    m_main_layout->addWidget(button_disconnect);

    setLayout(m_main_layout);
}

void WServer::set_visible(bool visible)
{
    m_active = visible;
    setVisible(visible);
}

void WServer::reset()
{
    m_add_pseudo->clear();
}

void WServer::reset_friends()
{
    for (size_t i = 0; i < m_friends.size(); ++i) {
        m_friends_layout->removeWidget(m_friends[i]->get_button());
        m_friends[i]->get_button()->setVisible(false);
    }
    m_friends.clear();
}

void WServer::set_friend(QPointer<Friend> friends)
{
    m_friends.push_back(friends);
    m_friends_layout->addWidget(friends->get_button());
}

void WServer::receive_call(const std::string &pseudo, const std::string &ip, int port)
{
    int res = QMessageBox::question(this, "Receive call", QString(std::string("You are receiving a call from " + pseudo + ". Hang up ?").data()),
        QMessageBox::Yes | QMessageBox::No);

    if (res == QMessageBox::Yes) {
        std::cout << "HANG UP" << std::endl;
        RecvCall call(m_client, this, ip, port);
        call.exec();
    }
}

void WServer::do_disconnect()
{
    m_client.do_disconnect();
}

void WServer::add_friend()
{
    if (m_add_pseudo->text().toStdString() == "")
        return;
    std::cout << "added " << m_add_pseudo->text().toStdString() << " in friend" << std::endl;
    request_t add_friend;
    add_friend.code = R_ADD_FRIEND;
    std::strcpy(add_friend.data._friend.sender, m_client.get_pseudo().data());
    std::strcpy(add_friend.data._friend.target, m_add_pseudo->text().toStdString().data());
    m_client.do_write(add_friend);
    m_add_pseudo->clear();
}