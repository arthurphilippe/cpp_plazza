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

int main()
{
	std::regex r("([0-9]{10})");

	std::string file("1234567890");
	std::smatch sm;

	if (regex_search(file, sm, r))
	{
		std::cout << "match" << std::endl;
		for (uint i=0; i<sm.size(); i++)
		{
			std::cout << sm[i] << std::endl;
		}
	}
}
