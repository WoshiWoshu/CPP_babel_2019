/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Database
*/

#pragma once

#include <deque>
#include <string>
#include <iostream>
#include <cstring>

#include "request.hpp"
#include "Profile.hpp"

typedef struct credentials_s {
    std::string uname;
    std::string pword;

    credentials_s(const std::string& u, const std::string& p) : uname(u), pword(p) {};
} credentials_t;

class Database {
	public:
		Database();
		~Database();

        void newGuest(Profile *);

        int login(login_t *);
        void signup(login_t *);
        void denyFriend(friend_t *);
        void acceptFriend(friend_t *);
        void friendRequest(friend_t *);

        Profile *findFromUname(const std::string&);
        Profile *findOffline(const std::string&);

        void erase(const Profile *const p);

	protected:
	private:
        std::deque<Profile *> guests;
        std::deque<credentials_t> credentials;
};
