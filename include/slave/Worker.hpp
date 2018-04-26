/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Worker
*/

#ifndef WORKER_HPP_
	#define WORKER_HPP_

	#include <memory>
	#include "ILink.hpp"

namespace plazza::slave {
	class Worker;
}

class plazza::slave::Worker {
public:
	Worker(unsigned int id, unsigned int threadNb);
	~Worker();
	void loop();
private:
	unsigned int		_id;
	unsigned int		_threadNb;
	std::unique_ptr<ILink>	_link;
};

#endif /* !WORKER_HPP_ */
