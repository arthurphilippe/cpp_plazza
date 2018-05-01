/*
** EPITECH PROJECT, 2018
**
** File description:
** Construct
*/

#include <thread>
#include "PlazzaGui.hpp"
#include "IUserController.hpp"

extern "C" {
	plazza::master::IUserController *Construct()
	{
		int ac = 1;
		char **av = NULL;
		QApplication *_app(new QApplication(ac, av));
		auto gui = new plazza::master::PlazzaGui(ac, av);

		_app->exec();
		return gui;
	}
}
