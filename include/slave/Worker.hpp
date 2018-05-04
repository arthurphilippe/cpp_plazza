/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Worker
*/

#ifndef SLAVE_WORKER_HPP_
	#define SLAVE_WORKER_HPP_

	#include <memory>
	#include <vector>
	#include <thread>
	#include <mutex>
	#include "ILink.hpp"

namespace plazza::slave {
	class Worker;
}

class plazza::slave::Worker {
public:
	Worker(unsigned int id, unsigned int threadNb);
	~Worker();
	void loop() noexcept;
private:
	void _wait();
	bool _pull(Command &cmd) noexcept;
	void _run(Command &cmd);

	unsigned int			_id;
	unsigned int			_threadNb;
	std::unique_ptr<ILink>		_link;
	std::vector<std::thread>	_threads;
	std::mutex			_mutexDown;
	std::mutex			_mutexUp;
	bool				_live;
};

#endif /* !SLAVE_WORKER_HPP_ */
