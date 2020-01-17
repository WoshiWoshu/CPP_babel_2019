/*
** EPITECH PROJECT, 2019
** client
** File description:
** WServer
*/

#ifndef WSERVER_H_
#define WSERVER_H_

#include <memory>
#include <vector>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>

class Friend;
class Client;

class WServer : public QWidget
{
Q_OBJECT

private:
    QApplication &m_app;
    Client &m_client;
    bool m_active;
    QPointer<QVBoxLayout> m_main_layout;
    QPointer<QVBoxLayout> m_friends_layout;
    QPointer<QLineEdit> m_add_pseudo;
    std::vector<QPointer<Friend>> m_friends;

public:
    WServer(QApplication &app, Client &client);
    ~WServer();

    void server_window();
    void set_visible(bool visible);
    void reset();
    void reset_friends();
    void set_friend(QPointer<Friend> friends);
    void receive_call(const std::string &pseudo, const std::string &ip, int port);

public slots:
    void do_disconnect();
    void add_friend();
};

#endif