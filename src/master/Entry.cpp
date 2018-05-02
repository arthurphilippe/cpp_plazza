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
	while (_workers.size()) {
		_stopFinishedWorkers();
		_recieveResults();
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
	_despatchQ.pop();
}

void Entry::_spawnWorker()
{
	_workers.emplace_back(new Worker(_threadNb, _workerIdBase++));
}

void Entry::_recieveResults()
{
	for (auto &worker : _workers) {
		worker->fillResults(_results);
	}
	for (auto &result : _results) {
		std::cout << result;
		_completeCommand(result);
	}
	_results.clear();
}

void Entry::_completeCommand(scrap::Result &result)
{
	for (auto it = _sentCommands.begin();
		it != _sentCommands.end() ; it++) {
		if (it->cmdId == result.id()) {
			_logger.logResult(*it, result);
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
			_workers.erase(it);
			_stopIdleWorkers();
			return;
		}
	}
}

void Entry::_stopFinishedWorkers()
{
	for (auto it = _workers.begin(); it != _workers.end(); it++) {
		if ((*it)->load() == 0) {
			(*it)->fillResults(_results);
			_workers.erase(it);
			_stopFinishedWorkers();
			return;
		}
	}
}
