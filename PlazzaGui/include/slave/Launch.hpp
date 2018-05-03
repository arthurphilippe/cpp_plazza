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
	constexpr auto SLAVE_BIN_NAME("plazza_slave");
	constexpr auto SLAVE_MAGIC("0x42ADF");
}

class plazza::slave::Launch {
public:
	Launch(unsigned int workerId, unsigned int threadNb);
	~Launch();
	void enter();
	void exec(const char *bin_path);
private:
	unsigned int _workerId;
	unsigned int _threadNb;
};

#endif /* !LAUNCH_HPP_ */
