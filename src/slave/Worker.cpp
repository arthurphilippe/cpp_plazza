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
	_threads(), _mutex(), _live(true)
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
		if (_pull(cmd) && cmd.cmdInfoType != NONE) {
			_run(cmd);
		}
	}
}

bool Worker::_pull(Command &cmd) noexcept
{
	plazza::ScopedLock guard(_mutex);
	if (!_live)
		return false;
	*_link >> cmd;
	std::cout << "Pulled " << cmd;
	if (cmd.cmdId == 0) {
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
	std::cout << *scrapper;
}

void Worker::_wait()
{
	for (std::thread &th : _threads) {
		th.join();
		plazza::ScopedLock guard(_mutex);
	}
}
