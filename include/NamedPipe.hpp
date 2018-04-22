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
	#include "ILink.hpp"

namespace Plazza {
	class NamedPipe;
	constexpr auto FIFO_MODE = 0666;
	constexpr auto MKFIFO_ERR = -1;
}

class Plazza::NamedPipe : public ILink {
public:
	NamedPipe(uint id, ILink::Mode mode);
	~NamedPipe();
	std::ostream &send(std::ostream &os) override;
	std::istream &recive(std::istream &in) override;
private:
	void _createFifos();
	std::string _nameIn;
	std::string _nameOut;
	std::ifstream _in;
	std::ofstream _out;
	ILink::Mode _mode;
};

#endif /* !NAMEDPIPE_HPP_ */
