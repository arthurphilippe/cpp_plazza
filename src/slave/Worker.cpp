/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Worker
*/

#include "ScopedLock.hpp"
#include "slave/Worker.hpp"
#include "NamedPipe.hpp"
#include "scrap/Factory.hpp"

using plazza::slave::Worker;
using scrapperptr = std::unique_ptr<plazza::scrap::IScrapper>;

Worker::Worker(unsigned int id, unsigned int threadNb)
	: _id(id), _threadNb(threadNb),
	_link(new plazza::NamedPipe(_id, NamedPipe::JOIN)),
	_threads(), _mutexDown(), _mutexUp(), _live(true)
{
	for (uint i = 0; i < _threadNb; i++) {
		_threads.emplace_back([&] { this->loop(); });
	}
	_wait();
}

Worker::~Worker()
{}

void Worker::loop() noexcept
{
	while (_live) {
		Command cmd;
		if (_pull(cmd)) {
			_run(cmd);
		}
	}
}

bool Worker::_pull(Command &cmd) noexcept
{
	plazza::ScopedLock guard(_mutexDown);
	if (!_live)
		return false;
	if (_link->eof()) {
		_live = false;
		return false;
	}
	*_link >> cmd;
	if (_link->eof()) {
		_live = false;
		return false;
	}
	if (cmd.cmdId == 0 || cmd.cmdInfoType == NONE) {
		_live = false;
		return false;
	}
	return true;
}

void Worker::_run(Command &cmd)
{
	scrapperptr scrapper(scrap::Factory::create(cmd.cmdInfoType));
	if (scrapper == nullptr)
		return;
	scrapper->run(cmd);
	plazza::ScopedLock guard(_mutexUp);
	*_link << *scrapper;
}

void Worker::_wait()
{
	for (std::thread &th : _threads) {
		th.join();
		plazza::ScopedLock guard(_mutexDown);
	}
}
