/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Entry
*/

#ifndef ENTRY_HPP_
	#define ENTRY_HPP_

	#include <queue>
	#include "master/Worker.hpp"
	#include "master/ControllerCLI.hpp"
	#include "Command.hpp"

namespace plazza::master {
	class Entry;
}

class plazza::master::Entry {
public:
	Entry(unsigned int threadNb);
	~Entry();
	void loop();
private:
	unsigned int			_threadNb;
	std::queue<Command>		_despatchQ;
	std::vector<Command>		_sentCommands;
	std::vector<Worker>		_workers;
	plazza::master::ControllerCLI	_controller;
};

#endif /* !ENTRY_HPP_ */
