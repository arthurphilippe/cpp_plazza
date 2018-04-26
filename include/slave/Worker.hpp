/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Worker
*/

#ifndef WORKER_HPP_
	#define WORKER_HPP_

namespace plazza::slave {
	class Worker;
}

class plazza::slave::Worker {
public:
	Worker(unsigned int id, unsigned int threadNb);
	~Worker();
	void loop();
private:
	unsigned int _id;
	unsigned int _threadNb;
};

#endif /* !WORKER_HPP_ */
