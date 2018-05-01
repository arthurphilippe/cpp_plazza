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
	_workerIdBase(1),
	_results(),
	_completedCommands()
{}

Entry::~Entry()
{}

void Entry::loop()
{
	while (_controller.poll(_despatchQ)) {
		_despatchTasks();
		_recieveResults();
		_stopIdleWorkers();
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

void Entry::_despatchTasks()
{
	for (auto &worker : _workers) {
		if (!_despatchQ.size())
			break;
		while (worker->load() < _threadNb && _despatchQ.size()
			&& _sentCommands.size() < 200) {
			std::this_thread::sleep_for(
				std::chrono::microseconds(100));
			_sendCmd(*worker);
		}
	}
	if (_workers.size() < MAX_WORKER_COUNT
		&& _despatchQ.size() > (_threadNb * _workers.size())) {
		_spawnWorker();
		_despatchTasks();
	}
}

void Entry::_sendCmd(Worker &worker)
{
	worker.send(_despatchQ.front());
	_sentCommands.push_back(_despatchQ.front());
	std::cout << "to : "<< worker.id() << " sent: " << _despatchQ.front();
	std::cout << "\n";
	_despatchQ.pop();
}

void Entry::_spawnWorker()
{
	_workers.emplace_back(new Worker(_threadNb, _workerIdBase++));
	std::cout << "spawned worker no: " << _workers.back()->id();
	std::cout << std::endl;
}

void Entry::_recieveResults()
{
	for (auto &worker : _workers) {
		worker->fillResults(_results);
	}
	if (_results.size())
		std::cout << "handling " << _results.size() << " result(s)\n";
	for (auto &result : _results) {
		std::cout << "===================" << std::endl;
		std::cout << result;
		_moveCompletedCommand(result);
	}
	_results.clear();
}

void Entry::_moveCompletedCommand(scrap::Result &result)
{
	for (auto it = _sentCommands.begin();
		it != _sentCommands.end() ; it++) {
		if (it->cmdId == result.id()) {
			_completedCommands.push_back(*it);
			_sentCommands.erase(it);
			return;
		}
	}
}

void Entry::_stopIdleWorkers()
{
	for (auto it = _workers.begin(); it != _workers.end(); it++) {
		if ((*it)->timedout()) {
			std::cout << "Stopped worker " << (*it)->id();
			std::cout << "\n";
			_workers.erase(it);
			_stopIdleWorkers();
			return;
		}
	}
}
