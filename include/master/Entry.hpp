/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Entry
*/

#ifndef ENTRY_HPP_
	#define ENTRY_HPP_

	#include <queue>
	#include <memory>
	#include "master/Worker.hpp"
	#include "master/ControllerCLI.hpp"
	#include "Command.hpp"

namespace plazza::master {
	class Entry;
	constexpr auto MAX_WORKER_COUNT(10);
	constexpr auto MAX_PENDING_CMD(200);
}

class plazza::master::Entry {
public:
	Entry(unsigned int threadNb);
	~Entry();
	void loop();
private:
	using workerptr = std::unique_ptr<Worker>;
	void _despatchTasks();
	void _sendCmd(Worker &);
	void _spawnWorker();
	void _recieveResults();
	void _moveCompletedCommand(scrap::Result &);
	void _stopIdleWorkers();

	unsigned int			_threadNb;
	std::queue<Command>		_despatchQ;
	std::vector<Command>		_sentCommands;
	std::vector<workerptr>		_workers;
	plazza::master::ControllerCLI	_controller;
	unsigned int			_workerIdBase;
	std::vector<scrap::Result>	_results;
	std::vector<Command>		_completedCommands;
};

#endif /* !ENTRY_HPP_ */
