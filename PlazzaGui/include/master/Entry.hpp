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
	#include "master/DynamicObject.hpp"

namespace plazza::master {
	class Entry;
}

class plazza::master::Entry {
public:
	Entry(unsigned int threadNb);
	~Entry();
	void loop();
private:
	using workerptr = std::unique_ptr<Worker>;
	using controllerptr = std::unique_ptr<IUserController>;
	using dynptr = std::unique_ptr<DynamicObject<IUserController>>;
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
	unsigned int			_workerIdBase;
	std::vector<scrap::Result>	_results;
	std::vector<Command>		_completedCommands;
	controllerptr			_controller;
	dynptr				_dynobj;
};

#endif /* !ENTRY_HPP_ */
