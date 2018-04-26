/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** NamedPipe
*/

#ifndef NAMEDPIPE_HPP_
	#define NAMEDPIPE_HPP_

	#include <string>
	#include <fstream>
	#include <thread>
	#include "ILink.hpp"

using namespace std::chrono_literals;

namespace plazza {
	class NamedPipe;
	constexpr auto FIFO_MODE = 0666;
	constexpr auto MKFIFO_ERR = -1;
}

class plazza::NamedPipe : public ILink {
public:
	NamedPipe(uint id, ILink::Mode mode);
	~NamedPipe();
	std::ostream &output() override
	{
		return _out;
	}
	std::istream &input() override
	{
		std::this_thread::sleep_for(10ms);
		return _in;
	}
private:
	void _createFifos();
	std::string _nameIn;
	std::string _nameOut;
	std::ifstream _in;
	std::ofstream _out;
	ILink::Mode _mode;
};

#endif /* !NAMEDPIPE_HPP_ */
