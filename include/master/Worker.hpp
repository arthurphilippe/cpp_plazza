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
	std::mutex		&_despatchQMtx;
	std::queue<Command>	&_despachQ;
	std::vector<Command>	_sentCommands;
	uint			_threadNb;
	uint			_id;
	std::unique_ptr<ILink>	_link;

	void _threadEntry();
	void _pullDespatch();
};

#endif /* !WORKER_HPP_ */
