/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** main
*/

#include <iostream>
#include <csignal>
#include <memory>

#include "slave/Launch.hpp"

#include "master/ControllerCLI.hpp"
#include "master/Manager.hpp"

static void start_child(char **av)
{
	plazza::slave::Launch launcher(std::stoi(av[1]), std::stoi(av[2]));
	launcher.enter();
}

static void start_controller(char **av)
{
	try {
		std::unique_ptr<plazza::master::ControllerCLI>
		controller(new plazza::master::ControllerCLI(av));
		controller.reset();
	} catch (plazza::slave::Launch &slaveLauncher) {
		slaveLauncher.exec(av[0]);
	}

}

int main(int ac, char **av)
{
	signal(SIGCHLD, SIG_IGN);
	if (ac >= 4 && strcmp(plazza::slave::SLAVE_MAGIC, av[3]) == 0) {
		start_child(av);
	} else if (ac == 2) {
		start_controller(av);
	} else {
		std::cerr << av[0] << ": arguments are invalid." << std::endl;
		return 84;
	}
	return 0;
}
