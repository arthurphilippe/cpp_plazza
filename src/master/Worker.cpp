/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Worker
*/

#include "master/Worker.hpp"
#include "slave/Launch.hpp"
#include <cstring>
#include "ScopedLock.hpp"
#include "NamedPipe.hpp"

using plazza::master::Worker;

Worker::Worker(std::pair<std::queue<Command> &, std::mutex &> &despatchQ,
		uint threadNb, uint workerId)
	: _despatchQMtx(despatchQ.second),
	_despachQ(despatchQ.first),
	_sentCommands(),
	_threadNb(threadNb),
	_id(workerId),
	_child(workerId, threadNb),
	_link(new NamedPipe(_id, NamedPipe::CREATE))
{
	Command test;

	test.cmdId = 0;
	test.cmdInfoType = NONE;
	test.cmdFileName = "j'aime les pates";
	*_link << test;
	*_link >> test;
}

Worker::~Worker()
{}

Worker::Child::Child(uint workerId, uint threadNb)
	: _pid(fork())
{
	if (_pid == 0)
		throw plazza::slave::Launch(workerId, threadNb);
	else if (_pid == -1) {
		std::string error("fork: ");
		error = error + strerror(errno);
		throw std::runtime_error(error.c_str());
	}
}

Worker::Child::~Child()
{}

void Worker::_threadEntry()
{
	if (_sentCommands.size() < _threadNb)
		_pullDespatch();
}

void Worker::_pullDespatch()
{
	plazza::ScopedLock guard(_despatchQMtx);

	while (_despachQ.size() && _sentCommands.size() < _threadNb) {
		_sentCommands.push_back(std::move(_despachQ.front()));
		_despachQ.pop();
	}
}
