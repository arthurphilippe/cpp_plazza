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

Worker::Worker(uint threadNb, uint workerId)
	// : _sentCommands(),
	: _threadNb(threadNb),
	_id(workerId),
	_child(workerId, threadNb),
	_link(new NamedPipe(_id, NamedPipe::CREATE)),
	_thread([&] (){ _threadEntry(); }),
	_live(true)
{
	// Command test;

	// test.cmdId = 1;
	// test.cmdInfoType = NONE;
	// test.cmdFileName = "j'aime les pates";
	// *_link << test;
}

Worker::~Worker()
{
	_live = false;
	_thread.join();
}

void Worker::fillResults(std::vector<scrap::Result> &results)
{
	plazza::ScopedLock guard(_lock);

	while (_results.size()) {
		results.push_back(_results.front());
		_results.pop_front();
	}
}

Worker::Child::Child(uint workerId, uint threadNb)
	: _pid()
{
	if (!workerId || !threadNb)
		return;
	_pid = fork();
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
	while (_live && !_link->eof()) {
		scrap::Result result;
		*_link >> result;
		if (result.contents().size())
			_register(result);
	}
}

void Worker::_register(scrap::Result &res)
{
	plazza::ScopedLock guard(_lock);

	_results.push_back(res);
}
