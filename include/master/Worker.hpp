/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Worker
*/

#ifndef WORKER_HPP_
	#define WORKER_HPP_

	#include <utility>
	#include <queue>
	#include <vector>
	#include <mutex>
	#include <memory>
	#include <unistd.h>
	#include "Command.hpp"
	#include "ILink.hpp"

namespace plazza::master {
	class Worker;
}

class plazza::master::Worker {
public:
	Worker(std::pair<std::queue<Command> &, std::mutex &> &,
		uint threadNb, uint workerId);
	~Worker();
private:
	class Child {
	public:
		Child(uint workerId, uint threadNb);
		~Child();
	private:
		pid_t _pid;
	};

	std::mutex		&_despatchQMtx;
	std::queue<Command>	&_despachQ;
	std::vector<Command>	_sentCommands;
	uint			_threadNb;
	uint			_id;
	Child			_child;
	std::unique_ptr<ILink>	_link;

	void _threadEntry();
	void _pullDespatch();
};

#endif /* !WORKER_HPP_ */
