/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** main
*/

#include <iostream>

#include <iostream>
#include <regex>
#include <fstream>
#include <thread>

#include "Command.hpp"
#include "Information.hpp"
#include "ScopedLock.hpp"
#include "NamedPipe.hpp"
#include "CommandParser.hpp"
#include "master/Worker.hpp"
#include "slave/Worker.hpp"
#include "slave/Launch.hpp"

#include "master/ControllerCLI.hpp"
#include "master/Entry.hpp"

int main()
{
	plazza::master::Entry toto(12);

	toto.loop();
	// std::queue<plazza::Command> cmdQ;
	// plazza::master::ControllerCLI kappa;

	// kappa.poll(cmdQ);

}

// int main()
// {
// 	std::queue<plazza::Command> commandQ;
// 	std::mutex mutex;
// 	std::pair<std::queue<plazza::Command> &, std::mutex &>
// 	queue(commandQ, mutex);

// 	try {
// 		plazza::master::Worker worker(queue, 4, 1);
// 	} catch (plazza::slave::Launch &slaveLauncher) {
// 		std::cout << "catched" << std::endl;
// 		slaveLauncher.enter();
// 		std::cout << "slave exited" << std::endl;
// 		return 0;
// 	} catch (const std::exception &exept) {
// 		exept.what();
// 		return 1;
// 	}
// 	std::this_thread::sleep_for(std::chrono::minutes(5));
// 	std::cout << "master exited" << std::endl;
// 	return 0;
// }

// int main(int ac, char **av)
// {
// 	std::queue<plazza::Command> kek;
// 	if (ac > 1)
// 	{
// 		std::string line(av[1]);
// 		plazza::CommandParser kappa(kek);
// 		kappa.ParseLine(line);
// 		kappa.dump();
// 	} else
// 		std::cout << "KEKVATEFAIR" << std::endl;
// }
