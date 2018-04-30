/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Entry
*/

#include "master/Entry.hpp"

using plazza::master::Entry;

Entry::Entry(unsigned int threadNb)
	: _threadNb(threadNb),
	_despatchQ(),
	_sentCommands(),
	_controller(),
	_workerIdBase(1)
{}

Entry::~Entry()
{}

void Entry::loop()
{
	while (_controller.poll(_despatchQ)) {
		_despatchTasks();
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

void Entry::_despatchTasks()
{
	for (auto &worker : _workers) {
		if (!_despatchQ.size())
			break;
		while (worker->load() < _threadNb && _despatchQ.size()) {
			_sendCmd(*worker);
		}
	}
	if (_despatchQ.size() > (_threadNb * _workers.size())) {
		_spawnWorker();
		_despatchTasks();
	}
}

void Entry::_sendCmd(Worker &worker)
{
	worker.send(_despatchQ.front());
	_sentCommands.push_back(_despatchQ.front());
	std::cout << "sent: " << _despatchQ.front();
	std::cout << "-> to: " << worker.id() << "\n";
	_despatchQ.pop();
}

void Entry::_spawnWorker()
{
	_workers.emplace_back(new Worker(_threadNb, _workerIdBase++));
	std::cout << "spawned: " << _workers.back()->id() << std::endl;
}
