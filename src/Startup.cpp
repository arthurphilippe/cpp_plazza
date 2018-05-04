/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Startup
*/

#include <csignal>
#include "Startup.hpp"
#include "slave/Launch.hpp"
#include "master/ControllerCLI.hpp"
#include "master/Manager.hpp"

using plazza::Startup;

/**
 * The Startup class handles the launch of the correct par of the
 * project using the provided arguments.
 *
 * The use of signal here allows children processes to exit properly
 * even if their parent is not waiting for them.
 */
Startup::Startup(int argc, char **argv)
	: ac(argc),
	av(argv)
{
	signal(SIGCHLD, SIG_IGN);
}

Startup::~Startup()
{}

int Startup::launch()
{
	auto ret(EXT_OK);

	if (ac == 4 && plazza::slave::SLAVE_MAGIC.compare(0, 6, av[3]))
		_startChild();
	else if (ac == 2) {
		_startMaster();
	}
	else {
		std::cerr << av[0] << INVALID_ARGS << std::endl;
		ret = EXT_ERR;
	}
	return ret;
}

void Startup::_startMaster()
{
	try {
		std::unique_ptr<plazza::master::ControllerCLI>
		controller(new plazza::master::ControllerCLI(av));
		controller.reset();
	} catch (plazza::slave::Launch &slaveLauncher) {
		slaveLauncher.exec(av[0]);
	}
}

void Startup::_startChild()
{
	plazza::slave::Launch launcher(std::stoi(av[1]), std::stoi(av[2]));
	launcher.enter();
}
