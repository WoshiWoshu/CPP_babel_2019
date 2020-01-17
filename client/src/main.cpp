//
// EPITECH PROJECT, 2018
// babel
// File description:
// 
//

#include <stdio.h>
#include <opus/opus.h>
#include <portaudio.h>

#include "../inc/Client.hpp"

int main(int ac, char **av)
{
	QApplication app(ac, av);
	Client client(app);

	return app.exec();
}