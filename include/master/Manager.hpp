/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Manager
*/

#ifndef ENTRY_HPP_
	#define ENTRY_HPP_

	#include <queue>
	#include <memory>
	#include "master/Worker.hpp"
	#include "Command.hpp"
	#include "Logger.hpp"

namespace plazza::master {
	class Manager;
	constexpr auto MAX_WORKER_COUNT(10);
	constexpr auto MAX_PENDING_CMD(200);
}

class plazza::master::Manager {
public:
	Manager(unsigned int threadNb, std::queue<Command> &despatchQ);
	~Manager();
	void manage();
	void wait();
private:
	using workerptr = std::unique_ptr<Worker>;
	void _despatchTasks();
	void _sendCmd(Worker &);
	void _spawnWorker();
	void _recieveResults();
	void _completeCommand(scrap::Result &);
	void _stopIdleWorkers();
	void _stopFinishedWorkers();

	unsigned int			_threadNb;
	std::queue<Command>		&_despatchQ;
	std::vector<Command>		_sentCommands;
	std::vector<workerptr>		_workers;
	unsigned int			_workerIdBase;
	std::vector<scrap::Result>	_results;
	// std::vector<Command>		_completedCommands;
	unsigned int			_completedCount;
	Logger				_logger;
};

#endif /* !ENTRY_HPP_ */
