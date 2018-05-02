/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Manager
*/

#include "master/Manager.hpp"

using plazza::master::Manager;

Manager::Manager(unsigned int threadNb, std::queue<Command> &despatchQ)
	: _threadNb(threadNb),
	_despatchQ(despatchQ),
	_sentCommands(),
	_workerIdBase(1),
	_results(),
	_completedCommands()
{}

Manager::~Manager()
{}

void Manager::manage()
{
	_despatchTasks();
	_recieveResults();
	_stopIdleWorkers();
}

void Manager::wait()
{
	_despatchTasks();
	while (_workers.size()) {
		_stopFinishedWorkers();
		_recieveResults();
	}
}

void Manager::_despatchTasks()
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

void Manager::_sendCmd(Worker &worker)
{
	worker.send(_despatchQ.front());
	_sentCommands.push_back(_despatchQ.front());
	_despatchQ.pop();
}

void Manager::_spawnWorker()
{
	_workers.emplace_back(new Worker(_threadNb, _workerIdBase++));
}

void Manager::_recieveResults()
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

void Manager::_completeCommand(scrap::Result &result)
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

void Manager::_stopIdleWorkers()
{
	for (auto it = _workers.begin(); it != _workers.end(); it++) {
		if ((*it)->timedout()) {
			_workers.erase(it);
			_stopIdleWorkers();
			return;
		}
	}
}

void Manager::_stopFinishedWorkers()
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
