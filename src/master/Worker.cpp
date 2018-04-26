/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Worker
*/

#include "master/Worker.hpp"
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
	_link(new NamedPipe(workerId, NamedPipe::CREATE))
{}

Worker::~Worker()
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
