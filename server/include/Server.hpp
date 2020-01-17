/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Server
*/

#pragma once

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h> //sockaddr, socklen_t
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <deque>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "request.hpp"
#include "Profile.hpp"
#include "Database.hpp"

#define INPUT_BUFFER_SIZE 100 //test: 100 bytes of buffer
#define DEFAULT_PORT 9034

class Server {
public:
    /*Server();
    Server(int port);
    Server(const Server& orig);*/
    Server(boost::asio::io_service& io_service, short port);
    virtual ~Server();

    void shutdown();
    void init();
    void loop();

    //callback setters
    uint16_t sendRequest(uint16_t conn, const char *messageBuffer, size_t);
    uint16_t sendRequest(uint16_t conn, char *messageBuffer, size_t);
    uint16_t sendRequest(uint16_t fd, requestCode);
    void forwardRequest(request_t *, const Profile&);

    Database db;

private:
    //fd_set file descriptor sets for use with FD_ macros
    fd_set masterfds;
    fd_set tempfds;

    //unsigned integer to keep track of maximum fd value, required for select()
    uint16_t maxfd;

    //socket file descriptors
    int mastersocket_fd; //master socket which receives new connections
    int tempsocket_fd; //temporary socket file descriptor which holds new clients

    //client connection data
    struct sockaddr_storage client_addr;
    //server socket details
    struct sockaddr_in servaddr;
    //input buffer
    char input_buffer[INPUT_BUFFER_SIZE];

    char remote_ip[INET6_ADDRSTRLEN];
    //int numbytes;

    //function prototypes
    void setup(int port);
    void initializeSocket();
    void bindSocket();
    void startListen();
    void handleNewConnection();
    void recvInputFromExisting(int fd);
    void clientLogout(int16_t);

    void start_accept();
    void handle_accept(Profile *, const boost::system::error_code&);

    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    //void *getInetAddr(struct sockaddr *saddr);
};