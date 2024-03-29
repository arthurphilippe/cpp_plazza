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

using plazza::NamedPipe;
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
		_out.open(_nameOut, std::ofstream::binary);
		_in.open(_nameIn, std::ofstream::binary);
	} else if (mode == Mode::JOIN) {
		std::this_thread::sleep_for(5ms);
		_in.open(_nameOut, std::ofstream::binary);
		_out.open(_nameIn, std::ofstream::binary);
	} else {
		throw LinkExeption("No mode specified.");
	}
	if (!_in || !_out) {
		throw LinkExeption("Failed to open pipe");
	}
}

NamedPipe::~NamedPipe()
{
	if (_mode == JOIN) {
		std::remove(_nameIn.c_str());
		std::remove(_nameOut.c_str());
	}
}

std::ostream &NamedPipe::output()
{
	return _out;
}

std::istream &NamedPipe::input()
{
	return _in;
}

bool NamedPipe::eof() const noexcept
{
	return _in.eof();
}

void NamedPipe::_createFifos()
{
	if (mkfifo(_nameIn.c_str(), FIFO_MODE) == MKFIFO_ERR && errno != 17) {
		throw LinkExeption(_nameIn + " ", errno);
	}
	if (mkfifo(_nameOut.c_str(), FIFO_MODE) == MKFIFO_ERR && errno != 17)
		throw LinkExeption(_nameOut + " ", errno);
}
