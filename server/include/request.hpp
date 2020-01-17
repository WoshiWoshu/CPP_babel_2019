/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** request
*/

#pragma once

#include <string>

#define UNAME_SIZE 20
#define PWORD_SIZE 20
#define IP_SIZE 20
#define MSG_MAX_SIZE 2048

typedef enum {
    R_NONE = 0,
    R_PING = 1,
    R_PLEASE_LOGIN = 2,
    R_UNDEFINED = 3,
    R_LOGIN = 4,
    R_SIGNUP = 5,
    R_LOGIN_SUCCESS = 6,
    R_SIGNUP_SUCCESS = 7,
    R_LOGIN_FAILURE = 8,
    R_SIGNUP_FAILURE = 9,
    R_ADD_FRIEND = 10,
    R_ACCEPT_FRIEND = 11,
    R_DENY_FRIEND = 12,
    R_SEND_MSG = 13,
    R_GET_ONLINE = 14,
    R_BEGIN_FRIEND = 15,
    R_BEGIN_FRIEND_REQ = 16,
    R_FRIEND_INFO = 17,
    R_FRIEND_REQ_INFO = 18,
    R_END_FRIEND = 19,
    R_END_FRIEND_REQ = 20,
    R_BAD_USERNAME = 21,
    R_SEND_CALL = 22,
    R_REICV_CALL = 23
} requestCode;

typedef struct login_s {
    uint8_t unameSize = 0; 
    uint8_t psswdize = 0;
    char username[UNAME_SIZE + 1] = {0};
    char password[PWORD_SIZE + 1] = {0};
} login_t;

typedef struct friend_s {
    char sender[UNAME_SIZE + 1] = {0};
    char target[UNAME_SIZE + 1] = {0};
} friend_t;

typedef struct msg_s {
    uint8_t msgSize = 0; 
    int32_t target = 0;
    char msg[MSG_MAX_SIZE + 1] = {0};
} msg_t;

typedef struct friend_info_s {
    char username[UNAME_SIZE + 1] = {0};
    char ip[IP_SIZE + 1] = {0};
    bool online = false;
} friend_info_t;

typedef struct call_s {
    char username[UNAME_SIZE + 1] = {0};
    char ip[IP_SIZE + 1] = {0};
    int port = 0;
} call_t;

struct requestData {
    login_t login;
    friend_t _friend;
    msg_t msg;
    friend_info_t friend_info;
    call_t call;
};

typedef struct request_s {
    uint8_t magic = 0x42;
    uint8_t code = R_NONE;
    struct requestData data;
} request_t;