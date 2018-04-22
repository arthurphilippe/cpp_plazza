/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** NamedPipe
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <iostream>
#include <sstream>
#include <thread>
#include <cstdio>
#include "NamedPipe.hpp"

using Plazza::NamedPipe;
using namespace std::chrono_literals;

NamedPipe::NamedPipe(uint id, ILink::Mode mode)
	: _nameIn(LINK_PREFIX + std::to_string(id)),
	_nameOut(LINK_PREFIX + std::to_string(id)),
	_mode(mode)
{
	_nameIn.append("_in");
	_nameOut.append("_out");
	if (mode == Mode::CREATE) {
		_createFifos();
		_out.open(_nameOut);
		_in.open(_nameIn, std::ifstream::in);
	} else {
		std::this_thread::sleep_for(10us);
		_in.open(_nameOut, std::ifstream::in);
		_out.open(_nameIn);
	}
}

NamedPipe::~NamedPipe()
{
	if (_mode == JOIN) {
		std::remove(_nameIn.c_str());
		std::remove(_nameOut.c_str());
	}
}

std::ostream &NamedPipe::send(std::ostream &os)
{
	// std::stringstream ss;
	// ss << os.rdbuf();
	// _out.write(ss.str().c_str(), ss.str().length());
	(void) os;
	return _out;
}

std::istream &NamedPipe::recive(std::istream &in)
{
	(void) in;
	return _in;
}

void NamedPipe::_createFifos()
{
	if (mkfifo(_nameIn.c_str(), FIFO_MODE) == MKFIFO_ERR)
		throw LinkExeption(_nameIn, errno);
	if (mkfifo(_nameOut.c_str(), FIFO_MODE) == MKFIFO_ERR)
		throw LinkExeption(_nameOut, errno);
}
