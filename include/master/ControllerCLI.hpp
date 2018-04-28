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
	#include <queue>
	#include "Command.hpp"

namespace plazza::master {
	class ControllerCLI;
	constexpr auto CMD_EXIT("exit");
}

class plazza::master::ControllerCLI {
public:
	ControllerCLI(std::istream &input = std::cin);
	~ControllerCLI();

	bool poll(std::queue<Command> &cmdQ);
private:
	static std::string	__getLine(std::istream *input);
	// static std::mutex	__mutex;

	bool		_nextLineReady();
	std::string	_getNextLine();

	std::unique_ptr<std::future<std::string>>	_nextLine;
	std::istream &_input;
};

#endif /* !CONTROLLERCLI_HPP_ */
