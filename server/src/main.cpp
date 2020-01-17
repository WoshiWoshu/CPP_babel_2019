/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** main
*/

#include <iostream>

#include "../include/Server.hpp"
#include "../include/Database.hpp"

// int main(int, char **)
// {
//     Server srv;

//     srv.init();
//     while (true)
//         srv.loop();
// }

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Please specify port" << std::endl;
        return 84;
    }
    try {
        boost::asio::io_service io_service;
        Server s(io_service, atoi(av[1]));

        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Server exception: " << e.what() << std::endl;
    }
    return 0;
}