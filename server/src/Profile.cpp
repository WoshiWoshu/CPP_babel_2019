/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Profile
*/

#include "../include/Profile.hpp"
#include "../include/Database.hpp"
#include <list>
#include <utility>

Profile::Profile(boost::asio::io_service& io_service, Database& d) : db(d)
{
    connected = GUEST;
    session.reset(new Session(io_service));
}

Profile::~Profile()
{
    session = nullptr;
}

Profile& Profile::operator=(const Profile& c)
{
    this->username = c.username;
    this->connected = c.connected;
    this->friendRequests = c.friendRequests;
    this->friends = c.friends;
    return *this;
}

void Profile::setStatus(Profile::status status)
{
    connected = status;
}

Profile::status Profile::getStatus() const
{
    return connected;
}

const std::string& Profile::getUsername() const
{
    return username;
}

void Profile::setUsername(const std::string& uname)
{
    username = uname;
}

void Profile::friendRequest(const std::string& name)
{
    friendRequests.push_back(name);
}

void Profile::acceptFriend(const std::string& name)
{
    std::cout << "accept friend" << std::endl;
    if (db.findFromUname(name) == nullptr)
        throw std::runtime_error("no such user");
    friends.push_back(name);
    db.findFromUname(name)->friends.push_back(username);
    removeFromRequests(name);
    std::cout << "accept friend 2" << std::endl;
    if (db.findFromUname(name)->getStatus() == Profile::ONLINE)
        db.findFromUname(name)->listFriends();
    listFriends();
}

void Profile::denyFriend(const std::string& name)
{
    removeFromRequests(name);
}

void Profile::removeFromRequests(const std::string& name)
{
    std::list<size_t> idx;

    if (!friendRequests.size())
        return;
    for (size_t i = 0; i < friendRequests.size(); ++i)
        if (friendRequests[i] == name)
            idx.push_back(i);
    for (auto i : idx)
        friendRequests.erase(friendRequests.begin() + i);
}

boost::asio::ip::tcp::socket& Profile::socket()
{
    return session->socket_;
}

void Profile::start()
{
    std::cout << "read some " << std::endl;
    session->socket_.async_read_some(boost::asio::buffer(session->data_, sizeof(request_t)),
        boost::bind(&Profile::handle_read, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void Profile::sendRequest(requestCode r)
{
    request_t requestForm;

    requestForm.code = r;
    boost::asio::async_write(session->socket_,
        boost::asio::buffer(&requestForm, sizeof(request_t)),
        boost::bind(&Profile::handle_write, this,
        boost::asio::placeholders::error));
}

void Profile::sendRequest(const request_t& r)
{
    boost::asio::async_write(session->socket_,
        boost::asio::buffer(&r, sizeof(request_t)),
        boost::bind(&Profile::handle_write, this,
        boost::asio::placeholders::error));
}

void Profile::handle_read(const boost::system::error_code& e, size_t)
{
    if (session == nullptr || e) {
        connected = OFFLINE;
        return;
    }
    request_t *request = reinterpret_cast<request_t *>(session->data_);

    std::cout << "req " << (unsigned int)request->code << std::endl;
    if (username == "" || connected != ONLINE)
        if (request->code != R_LOGIN && request->code != R_SIGNUP) {
            sendRequest(R_PLEASE_LOGIN);
            return;
        }
    switch (request->code) {
    case R_LOGIN:
        std::cout << "try login" << std::endl;
        try {
            login(reinterpret_cast<login_t *>(&request->data.login));
            sendRequest(R_LOGIN_SUCCESS);
            listFriends();
        } catch (...) {
            try {
                signup(reinterpret_cast<login_t *>(&request->data.login));
                sendRequest(R_SIGNUP_SUCCESS);
            } catch (...) {
                sendRequest(R_SIGNUP_FAILURE);
            }
        }
        break;
    case R_SIGNUP:
        try {
            signup(reinterpret_cast<login_t *>(&request->data.login));
            sendRequest(R_SIGNUP_SUCCESS);
        } catch (...) {
            sendRequest(R_SIGNUP_FAILURE);
        }
        break;
    case R_ADD_FRIEND:
        try {
            db.friendRequest(reinterpret_cast<friend_t *>(&request->data._friend));
        } catch (...) {
            sendRequest(R_BAD_USERNAME);
        }
        break;
    case R_ACCEPT_FRIEND:
        acceptFriend(reinterpret_cast<friend_t *>(&request->data._friend)->target);
        break;
    case R_DENY_FRIEND:
        denyFriend(reinterpret_cast<friend_t *>(&request->data._friend)->target);
        break;
    case R_PING:
        std::cout << "ping" << std::endl;
        sendRequest(R_PING);
        break;
    case R_SEND_CALL:
        try {
            sendCall(*request);
        } catch (...) {
            sendRequest(R_BAD_USERNAME);
        }
        break;
/*    case R_SEND_MSG:
        forwardRequest(request, db.findFromUname(request->data.msg.target));
        break;*/
    }
}

void Profile::handle_write(const boost::system::error_code& error)
{
    if (!error) {
        session->socket_.async_read_some(boost::asio::buffer(session->data_, sizeof(request_t)),
            boost::bind(&Profile::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
      delete this;
}

void Profile::login(login_t *l)
{
    db.login(l);
    connected = ONLINE;
    username = l->username;
    for (Profile *p = db.findOffline(l->username); p != nullptr; p = db.findOffline(l->username)) {
        friends = p->friends;
        db.erase(p);
    }
}

void Profile::signup(login_t *l)
{
    db.signup(l);
    connected = ONLINE;
    username = l->username;
}

void Profile::listFriendRequests()
{
/*    request_t r;

    sendRequest(R_BEGIN_FRIEND_REQ);
    for (auto _friend : friendRequests) {
        std::strcpy(r.data.friend_info, _friend
    }
    sendRequest(R_END_FRIEND_REQ);*/
}

const std::string Profile::getIP() const
{
    return session->socket_.remote_endpoint().address().to_string();
}

void Profile::listFriends()
{
    request_t r;

    std::memset(&r, 0, sizeof(request_t));
    r.code = R_FRIEND_INFO;
    sendRequest(R_BEGIN_FRIEND);
    std::cout << "friend begin" << std::endl;
    for (auto _friend : friends) {
        std::memcpy(r.data.friend_info.username, _friend.c_str(), UNAME_SIZE + 1);
        std::memcpy(r.data.friend_info.ip, db.findFromUname(_friend)->getIP().c_str(), UNAME_SIZE + 1);
        r.data.friend_info.online = (db.findFromUname(_friend)->connected == ONLINE ? true : false);
        sendRequest(r);
        std::cout << "friend " << r.data.friend_info.username << " st " << r.data.friend_info.online << std::endl;
    }
    sendRequest(R_END_FRIEND);
}

void Profile::sendCall(request_t& r)
{
    std::string target(r.data.call.username);

    if (db.findFromUname(r.data.call.username) == nullptr)
        throw std::runtime_error("no such user");
    r.code = R_REICV_CALL;
    strncpy(r.data.call.ip, getIP().c_str(), IP_SIZE);
    strncpy(r.data.call.username, username.c_str(), UNAME_SIZE);
    db.findFromUname(target)->sendRequest(r);
}