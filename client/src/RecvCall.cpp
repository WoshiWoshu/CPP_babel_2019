/*
** EPITECH PROJECT, 2019
** src
** File description:
** RecvCall
*/

#include <iostream>
#include <cstring>
#include <QtCore/QPointer>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtNetwork/QNetworkDatagram>

#include "../inc/RecvCall.hpp"

RecvCall::RecvCall(Client &client, QWidget *parent, std::string ip, int port)
    : QDialog(), m_client(client), m_ip(ip), m_port(port)
{
    setWindowTitle("Calling ...");
    QPointer<QPushButton> button_stop = new QPushButton("Stop");
    connect(button_stop, &QPushButton::clicked, this, &RecvCall::stop);
    QPointer<QVBoxLayout> main_layout = new QVBoxLayout;
    main_layout->addWidget(button_stop);
    setLayout(main_layout);
    call();
}

RecvCall::~RecvCall()
{

}

void RecvCall::call()
{
    m_socket = new QUdpSocket;
    m_socket->bind(0);
    connect(m_socket, &QUdpSocket::readyRead, this, &RecvCall::ready_read);
    connect(m_socket, &QUdpSocket::connected, this, &RecvCall::connected);
    connect(m_socket, &QUdpSocket::disconnected, this, &RecvCall::disconnected);
    m_socket->connectToHost(QHostAddress(m_ip.data()), m_port);
    if (!m_socket->waitForConnected())
        return;
    // while (true) {
    //     paData d = m_rec.recVoice();
    //     char *data = reinterpret_cast<char *>(&d);
    //     m_socket->write(data, sizeof(paData));
    // }
}

void RecvCall::ready_read()
{
    while (m_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_socket->receiveDatagram();
        std::cout << datagram.data().data() << std::endl;
    }
}

void RecvCall::connected()
{
    std::cout << "call connected !" << std::endl;
    int p = m_socket->localPort();
    char *port = reinterpret_cast<char *>(&p);
    m_socket->write(port, sizeof(int));
}

void RecvCall::disconnected()
{
    std::cout << "call disconnected !" << std::endl;
    close();
}

void RecvCall::stop()
{
    m_socket->disconnectFromHost();
    close();
}