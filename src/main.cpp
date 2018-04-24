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

int main(int ac, char **av)
{
	std::queue<Plazza::Command> kek;
	if (ac > 1)
	{
		std::string line(av[1]);
		Plazza::CommandParser kappa(kek);
		kappa.ParseLine(line);
	} else
		std::cout << "KEKVATEFAIR" << std::endl;
}
