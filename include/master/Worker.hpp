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
	void send(const Command &);
	void fillResults(std::vector<scrap::Result> &);
	uint load() const noexcept
	{
		return _load;
	}
	uint id() const noexcept
	{
		return _id;
	}
	bool timedout() const noexcept;
private:
	using timept =
		std::chrono::time_point<std::chrono::system_clock>;

	class Child {
	public:
		Child(uint workerId, uint threadNb);
		~Child();
	private:
		pid_t _pid;
	};

	uint			_threadNb;
	uint			_id;
	Child			_child;
	std::unique_ptr<ILink>	_link;
	bool			_live;
	std::thread		_thread;
	uint			_load;
	timept			_idleSince;

	std::list<scrap::Result>	_results;
	void _threadEntry();
	std::mutex			_lock;
	void _register(scrap::Result &);
};

#endif /* !WORKER_HPP_ */
