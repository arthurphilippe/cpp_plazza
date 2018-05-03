/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ControllerCLI
*/

#ifndef CONTROLLERCLI_HPP_
	#define CONTROLLERCLI_HPP_

	#include <string>
	#include <memory>
	#include <future>
	#include <iostream>
	#include "master/IUserController.hpp"
	#include "master/Manager.hpp"
	#include "CommandParser.hpp"

namespace plazza::master {
	class ControllerCLI;
	constexpr auto CMD_EXIT("exit");
}

class plazza::master::ControllerCLI : public IUserController {
public:
	ControllerCLI(char **av, std::istream &input = std::cin);
	~ControllerCLI();

private:
	static std::string	__getLine(std::istream *input);

	bool			_nextLineReady();
	std::string		_getNextLine();

	uint				_threadNb;
	const std::string		_binName;
	bool				_live;
	std::istream			&_input;
	std::future<std::string>	_nextLine;
	std::queue<Command>		_cmdQ;
	CommandParser			_parser;
	Manager				_manager;
};

#endif /* !CONTROLLERCLI_HPP_ */
