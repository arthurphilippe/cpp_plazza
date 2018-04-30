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
	#include <list>
	#include <mutex>
	#include <memory>
	#include <unistd.h>
	#include <thread>
	#include "Command.hpp"
	#include "scrap/Result.hpp"
	#include "ScopedLock.hpp"
	#include "ILink.hpp"

namespace plazza::master {
	class Worker;
}

class plazza::master::Worker {
public:
	Worker(uint threadNb, uint workerId);
	~Worker();
	void fillResults(std::vector<scrap::Result> &);
private:
	class Child {
	public:
		Child(uint workerId, uint threadNb);
		~Child();
	private:
		pid_t _pid;
	};

	// std::list<Command>	_sentCommands;
	uint			_threadNb;
	uint			_id;
	Child			_child;
	std::unique_ptr<ILink>	_link;
	std::thread		_thread;
	bool			_live;

	std::list<scrap::Result>	_results;
	std::mutex			_lock;
	void _threadEntry();
	void _register(scrap::Result &);
};

#endif /* !WORKER_HPP_ */
