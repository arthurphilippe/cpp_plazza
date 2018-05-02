/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ControllerCLI
*/

#include <iostream>
#include "master/ControllerCLI.hpp"
#include "slave/Launch.hpp"

using plazza::master::ControllerCLI;

ControllerCLI::ControllerCLI(char **av, std::istream &input)
	: _threadNb(std::stoi(av[1])),
	_binName(av[0]),
	_live(true),
	_input(input),
	_nextLine(std::async(__getLine, &_input)),
	_cmdQ(),
	_parser(_cmdQ),
	_manager(_threadNb, _cmdQ)
{
	while (_live) {
		while (_nextLineReady()) {
			auto line = _getNextLine();
			if (line == CMD_EXIT) {
				return;
			}
			_parser.ParseLine(line);
		}
		try {
			_manager.manage();
		} catch (slave::Launch &slaveLauncher) {
			slaveLauncher.exec(_binName.c_str());
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

ControllerCLI::~ControllerCLI()
{
	try {
		_manager.wait();
	} catch (slave::Launch &slaveLauncher) {
		slaveLauncher.exec(_binName.c_str());
	}
	_nextLine.get();
}

bool ControllerCLI::_nextLineReady()
{
	auto ret = _nextLine.wait_for(std::chrono::milliseconds(10));

	return ret == std::future_status::ready;
}

std::string ControllerCLI::_getNextLine()
{
	std::string line = _nextLine.get();

	_nextLine = std::async(__getLine, &_input);
	return line;
}

std::string ControllerCLI::__getLine(std::istream *input)
{
	std::string str;

	if (std::getline(*input, str)) {
		return str;
	}
	return CMD_EXIT;
}
