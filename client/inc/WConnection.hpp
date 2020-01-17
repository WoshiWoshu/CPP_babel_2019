/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Window
*/

#ifndef WCONNECTION_H_
#define WCONNECTION_H_

#include <memory>
#include <QtCore/QPointer>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QInputDialog>

class Client;

class WConnection : public QWidget
{
Q_OBJECT

private:
    QApplication &m_app;
    Client &m_client;
    QPointer<QLineEdit> m_pseudo;
    QPointer<QLineEdit> m_passwd;
    QPointer<QLineEdit> m_server_ip;
    QPointer<QLineEdit> m_server_port;

public:
    WConnection(QApplication &app, Client &client);
    ~WConnection();

    void connection_window();
    void reset();

public slots:
    void connect();
};

#endif