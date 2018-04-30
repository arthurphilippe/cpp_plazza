/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ControllerCLI
*/

#include <iostream>
#include "master/ControllerCLI.hpp"
#include "CommandParser.hpp"

using plazza::master::ControllerCLI;

ControllerCLI::ControllerCLI(std::istream &input)
	: _input(input),
	_nextLine(std::async(__getLine, &_input))
{}

ControllerCLI::~ControllerCLI()
{
	_nextLine.get();
}

bool ControllerCLI::poll(std::queue<Command> &cmdQ)
{
	CommandParser parser(cmdQ);
	bool ret(false);

	while (_nextLineReady()) {
		auto line = _getNextLine();
		if (line == CMD_EXIT)
			return ret;
		std::cout << "Processing: \"" << line << "\"" << std::endl;
		parser.ParseLine(line);
		ret = true;
	}
	return true;
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
