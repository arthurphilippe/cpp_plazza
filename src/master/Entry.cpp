/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Entry
*/

#include "master/Entry.hpp"

using plazza::master::Entry;

Entry::Entry(unsigned int threadNb)
	: _threadNb(threadNb),
	_despatchQ(),
	_sentCommands(),
	_controller()
{}

Entry::~Entry()
{}

void Entry::loop()
{
	while (_controller.poll(_despatchQ)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		// std::cout << "toto\n";
	}
}
