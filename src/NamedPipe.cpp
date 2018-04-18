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
#include "NamedPipe.hpp"

using Plazza::NamedPipe;

NamedPipe::NamedPipe(uint id, ILink::Mode mode)
	: _nameIn(LINK_PREFIX + id),
	_nameOut(LINK_PREFIX + id)
{
	_nameIn.append("_in");
	_nameOut.append("_out");
	if (mode == Mode::CREATE) {
		_createFifos();
		_in.open(_nameIn);
		_out.open(_nameOut);
	} else {
		_in.open(_nameOut);
		_out.open(_nameIn);
	}
}

NamedPipe::~NamedPipe()
{}

std::ostream &NamedPipe::send(std::ostream &os)
{
	std::stringstream ss;
	ss << os.rdbuf();
	_out.write(ss.str().c_str(), ss.str().length());
	return os;
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
