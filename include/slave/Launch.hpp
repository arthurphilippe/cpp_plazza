/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Launch
*/

#ifndef LAUNCH_HPP_
	#define LAUNCH_HPP_

	#include "Worker.hpp"

namespace plazza::slave {
	class Launch;
}

class plazza::slave::Launch {
public:
	Launch(unsigned int workerId, unsigned int threadNb);
	~Launch();
	void enter();
private:
	unsigned int _workerId;
	unsigned int _threadNb;
};

#endif /* !LAUNCH_HPP_ */
