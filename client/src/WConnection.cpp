/*
** EPITECH PROJECT, 2019
** babel
** File description:
** Window
*/

#include <iostream>
#include <string>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtCore/QPointer>

#include "../inc/WConnection.hpp"
#include "../inc/Client.hpp"

WConnection::WConnection(QApplication &app, Client &client)
    : QWidget(), m_app(app), m_client(client)
{
    setWindowTitle("Connection");
    connection_window();
}

WConnection::~WConnection()
{

}

void WConnection::connection_window()
{
    m_pseudo = new QLineEdit;
    m_passwd = new QLineEdit;
    m_server_ip = new QLineEdit;
    m_server_port = new QLineEdit;
    m_pseudo->setMaxLength(UNAME_SIZE);
    m_passwd->setMaxLength(UNAME_SIZE);

    QPointer<QFormLayout> form_layout = new QFormLayout;
    form_layout->addRow("Pseudo :", m_pseudo);
    form_layout->addRow("Password :", m_passwd);
    form_layout->addRow("Server ip :", m_server_ip);
    form_layout->addRow("Server port :", m_server_port);

    QPointer<QPushButton> ok = new QPushButton("OK");
    QWidget::connect(ok, SIGNAL(clicked()), this, SLOT(connect()));

    QPointer<QVBoxLayout> main_layout = new QVBoxLayout;
    main_layout->addLayout(form_layout);
    main_layout->addWidget(ok);

    setLayout(main_layout);
}

void WConnection::reset()
{
    m_pseudo->clear();
    m_passwd->clear();
    m_server_ip->clear();
    m_server_port->clear();
}

void WConnection::connect()
{
    if (m_pseudo->text() == "" || m_passwd->text() == "" || m_server_ip->text() == "" || m_server_port->text() == "")
        return;
    std::cout << "connect" << std::endl;
    m_client.set_pseudo(m_pseudo->text().toStdString());
    m_client.do_connect(m_pseudo->text().toStdString(), m_passwd->text().toStdString(), m_server_ip->text().toStdString(), m_server_port->text().toInt());
}