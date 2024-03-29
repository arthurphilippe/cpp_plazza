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
	*_link << plazza::Command{"stop", NONE, 0};
	_link->closeUpstream();
	_thread.join();
}

void Worker::send(const Command &cmd)
{
	plazza::ScopedLock guard(_lock);
	_load += 1;
	*_link << cmd;
}

void Worker::fillResults(std::list<scrap::Result> &results)
{
	plazza::ScopedLock guard(_lock);

	while (_results.size()) {
		results.push_back(_results.front());
		_results.pop_front();
	}
}

bool Worker::timedout() const noexcept
{
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration(now - _idleSince);

	return (_load == 0 && _results.size() == 0
		&& duration > std::chrono::seconds(5));
}

Worker::Child::Child(uint workerId, uint threadNb)
	: _pid()
{
	if (!workerId || !threadNb)
		return;
	_pid = fork();
	if (_pid == 0) {
		throw plazza::slave::Launch(workerId, threadNb);
	}
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
		if (!_spaceLeftInResults()) {
			std::this_thread::sleep_for(
				std::chrono::milliseconds(10));
			continue;
		}
		*_link >> result;
		if (result.id() != 0)
			_register(result);
	}
}

void Worker::_register(scrap::Result &res)
{
	plazza::ScopedLock guard(_lock);

	_results.push_back(res);
	if (_load != 0)
		_load -= 1;
	if (_load == 0)
		_idleSince = std::chrono::high_resolution_clock::now();
}

bool Worker::_spaceLeftInResults()
{
	plazza::ScopedLock guard(_lock);

	return _results.size() < 2;
}
