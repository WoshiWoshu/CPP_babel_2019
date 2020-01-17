/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Profile
*/

#pragma once

#include <string>
#include <deque>
#include <memory>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "request.hpp"

#define DATA_LENGTH 1024

class Database;

struct Session {
    Session(boost::asio::io_service& io_service) : socket_(io_service) {};

    boost::asio::ip::tcp::socket socket_;
    char data_[sizeof(request_t)];
};

class Profile {
	public:
        enum status {
            OFFLINE,
            GUEST,
            ONLINE
        };

		/*Profile();
        Profile(int16_t);*/
        Profile(boost::asio::io_service&, Database&);
		~Profile();

        void setStatus(status);
        void setUsername(const std::string&);
        void setFd(const int8_t);
        void addFriend(const std::string&);
        void acceptFriend(const std::string& name);
        void denyFriend(const std::string& name);
        void removeFromRequests(const std::string& name);
        void login(login_t *);
        void signup(login_t *);
        void sendCall(request_t&);
        void listFriendRequests();
        void listFriends();

        status getStatus() const;
        const std::string getIP() const;
        const std::string& getUsername() const;

        void start();
        boost::asio::ip::tcp::socket& socket();

        Profile& operator=(const Profile&);
        void friendRequest(const std::string& name);
        
        void sendRequest(requestCode);
        void sendRequest(const request_t&);

        std::shared_ptr<Session> session;

	protected:
        status connected;
        std::string username;
        std::deque<std::string> friends;
        std::deque<std::string> friendRequests;
        Database& db;

        void handle_read(const boost::system::error_code&, size_t);
        void handle_write(const boost::system::error_code&);
	private:
};
