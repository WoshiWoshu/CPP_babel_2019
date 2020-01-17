/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Server
*/

#include "../include/Server.hpp"

/*Server::Server() : Server(DEFAULT_PORT)
{
}

Server::Server(int port) : db()
{
    setup(port);
}

Server::Server(const Server& orig)
{
}*/

Server::Server(boost::asio::io_service& io_service, short port)
: io_service_(io_service), acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    start_accept();
}


Server::~Server()
{
#ifdef SERVER_DEBUG
    std::cout << "[SERVER] [DESTRUCTOR] Destroying Server...\n";
#endif
    close(mastersocket_fd);
}

void Server::start_accept()
{
    Profile *new_session = new Profile(io_service_, db);

    acceptor_.async_accept(new_session->socket(),
        boost::bind(&Server::handle_accept, this, new_session,
        boost::asio::placeholders::error));
}

void Server::handle_accept(Profile *new_session, const boost::system::error_code& error)
{
    if (!error) {
        db.newGuest(new_session);
        new_session->start();
        std::cout << "new connection" << std::endl;
    } else
        delete new_session;
    start_accept();
}

uint16_t Server::sendRequest(uint16_t fd, char *messageBuffer, size_t size)
{
    return send(fd, messageBuffer, size, 0);
}

uint16_t Server::sendRequest(uint16_t fd, const char *messageBuffer, size_t size)
{
    return send(fd, messageBuffer, size, 0);
}

uint16_t Server::sendRequest(uint16_t fd, requestCode r)
{
    request_t requestForm;

    requestForm.code = r;
    return send(fd, &requestForm, sizeof(request_t) - sizeof(struct requestData), 0);
}

void Server::forwardRequest(request_t *, const Profile&)
{
}