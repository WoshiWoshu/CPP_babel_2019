/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Database
*/

#include <stdexcept>

#include "../include/Database.hpp"

Database::Database()
{
}

Database::~Database()
{
}

int Database::login(login_t *form)
{
    for (auto p : credentials)
        if (std::string(form->username) == p.uname)
            if (std::string(form->password) == p.pword)
                return 0;
    throw std::runtime_error("Wrong password");
}

void Database::signup(login_t *form)
{
    for (auto p : credentials)
        if (std::string(form->username) == p.uname)
            throw std::runtime_error("Wrong password");
    credentials.push_back(credentials_t(std::string(form->username), std::string(form->password)));
}

void Database::newGuest(Profile *p)
{
    guests.push_back(p);
}

void Database::friendRequest(friend_t *profile)
{
    if (findFromUname(profile->target) == nullptr)
        throw std::runtime_error("no such user");
    findFromUname(profile->target)->acceptFriend(profile->sender);
/*    findFromUname(profile->target)->friendRequest(profile->sender);
    if (findFromUname(profile->target)->getStatus() == Profile::ONLINE)
        findFromUname(profile->target)->listFriendRequests();*/
}

Profile *Database::findFromUname(const std::string& name)
{
    for (auto p : guests)
        if (name == p->getUsername())
            return p;
    return nullptr;   
}

Profile *Database::findOffline(const std::string& name)
{
    for (auto p : guests)
        if (name == p->getUsername() && p->getStatus() == Profile::OFFLINE)
            return p;
    return nullptr;   
}

void Database::erase(const Profile *const p)
{
    for (int i = guests.size() - 1; i >= 0 && (unsigned)i > guests.size(); --i)
        if (guests[i] == p)
            guests.erase(guests.begin() + i);
}