/*
** EPITECH PROJECT, 2019
** src
** File description:
** Calling
*/

#include <iostream>
#include <cstring>
#include <QtCore/QPointer>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtNetwork/QNetworkDatagram>
#include "../inc/Calling.hpp"

Calling::Calling(Client &client, QWidget *parent, std::string pseudo)
    : QDialog(parent), m_client(client), m_pseudo(pseudo), m_connected(false)
{
    setWindowTitle("Calling ...");
    QPointer<QPushButton> button_stop = new QPushButton("Stop");
    connect(button_stop, &QPushButton::clicked, this, &Calling::stop);
    QPointer<QVBoxLayout> main_layout = new QVBoxLayout;
    main_layout->addWidget(button_stop);
    setLayout(main_layout);
    call();
}

Calling::~Calling()
{

}

void Calling::call()
{
    m_socket = new QUdpSocket;
    m_socket->bind(0);
    connect(m_socket, &QUdpSocket::readyRead, this, &Calling::ready_read);
    connect(m_socket, &QUdpSocket::connected, this, &Calling::connected);
    connect(m_socket, &QUdpSocket::disconnected, this, &Calling::disconnected);
    std::cout << "UDP port : " << m_socket->localPort() << std::endl;
    request_t req;
    req.code = R_SEND_CALL;
    req.data.call.port = m_socket->localPort();
    std::cout << m_pseudo << std::endl;
    std::strcpy(req.data.call.username, m_pseudo.data());
    m_client.do_write(req);
}

void Calling::ready_read()
{
    while (m_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_socket->receiveDatagram();
        if (!m_connected) {
            int port = 0;
            std::memcpy(&port, datagram.data().data(), sizeof(int));
            m_socket->connectToHost(datagram.senderAddress(), port);
            m_connected = true;
        } else {
            paData data;
            std::memcpy(&data, datagram.data().data(), sizeof(paData));
            m_rec.playVoice(data);
        }
    }
}

void Calling::connected()
{
    std::cout << "call connected !" << std::endl;
}

void Calling::disconnected()
{
    std::cout << "call disconnected !" << std::endl;
    close();
}

void Calling::stop()
{
    m_socket->disconnectFromHost();
    close();
}
