/*
** EPITECH PROJECT, 2018
**
** File description:
** Construct
*/

#include <iostream>
#include <thread>
#include "PlazzaGui.hpp"
#include "IUserController.hpp"

extern "C" {
	plazza::master::IUserController *Construct(char *arg)
	{
		int ac = 1;
		char **av = NULL;
		QApplication *_app(new QApplication(ac, av));
		auto gui = new plazza::master::PlazzaGui(arg);
		_app->exec();
		return gui;
	}
}
