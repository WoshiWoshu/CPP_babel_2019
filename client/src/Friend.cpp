/*
** EPITECH PROJECT, 2019
** src
** File description:
** Friend
*/

#include <iostream>
#include <QtCore/QString>

#include "../inc/Friend.hpp"
#include "../inc/Calling.hpp"

Friend::Friend(Client &client, std::string pseudo, std::string ip, bool is_connected)
    : QWidget(), m_client(client), m_button(new QPushButton(QString(pseudo.data()))), m_pseudo(pseudo), m_ip(ip), m_is_connected(is_connected)
{
    if (is_connected)
        m_button->setStyleSheet("background-color: green");
    else
        m_button->setStyleSheet("background-color: red");
    QWidget::connect(m_button, SIGNAL(clicked()), this, SLOT(do_call()));    
}

Friend::~Friend()
{

}

const QPointer<QPushButton> Friend::get_button()
{
    return m_button;
}

void Friend::do_call()
{
    std::cout << "calling !" << std::endl;
    Calling call(m_client, this, m_pseudo);
    call.exec();
}