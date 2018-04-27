/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Worker
*/

#include "ScopedLock.hpp"
#include "slave/Worker.hpp"
#include "NamedPipe.hpp"

using plazza::slave::Worker;

Worker::Worker(unsigned int id, unsigned int threadNb)
	: _id(id), _threadNb(threadNb),
	_link(new plazza::NamedPipe(_id, NamedPipe::JOIN)),
	_threads(), _mutex(), _tester(0)
{
	for (uint i = 0; i < _threadNb; i++) {
		_threads.emplace_back([&] { this->loop(); });
	}
	_wait();
}

Worker::~Worker()
{}

void Worker::loop()
{
	plazza::ScopedLock guard(_mutex);

	_tester += 1;
	std::cout << "tester: " << _tester << std::endl;
}

void Worker::_wait()
{
	for (std::thread &th : _threads) {
		th.join();
		plazza::ScopedLock guard(_mutex);
		std::cout << "One more joined" << std::endl;
	}
}
