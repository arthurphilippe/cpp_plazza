/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Worker
*/

#include <cstring>
#include <iostream>
#include "master/Worker.hpp"
#include "slave/Launch.hpp"
#include "ScopedLock.hpp"
#include "NamedPipe.hpp"

using plazza::master::Worker;

Worker::Worker(uint threadNb, uint workerId)
	: _threadNb(threadNb),
	_id(workerId),
	_child(_id, _threadNb),
	_link(new NamedPipe(_id, NamedPipe::CREATE)),
	_live(true),
	_thread([&] (){ _threadEntry(); }),
	_load(0)
{}

Worker::~Worker()
{
	_live = false;
	_link->closeUpstream();
	_thread.join();
}

void Worker::send(const Command &cmd)
{
	plazza::ScopedLock guard(_lock);
	_load += 1;
	*_link << cmd;
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
		if (result.id())
			_register(result);
	}
}

void Worker::_register(scrap::Result &res)
{
	plazza::ScopedLock guard(_lock);

	_results.push_back(res);
	std::cout << "result: " << res << std::endl;
	_load -= 1;
}
