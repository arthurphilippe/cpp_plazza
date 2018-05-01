/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Launch
*/

#include <unistd.h>
#include <string>
#include "slave/Launch.hpp"

using plazza::slave::Launch;

Launch::Launch(unsigned int workerId, unsigned int threadNb)
	: _workerId(workerId), _threadNb(threadNb)
{}

Launch::~Launch()
{}

void Launch::enter()
{
	plazza::slave::Worker worker(_workerId, _threadNb);
}

void Launch::exec(const char *bin_path)
{
	execl(bin_path, SLAVE_BIN_NAME, std::to_string(_workerId).c_str(),
		std::to_string(_threadNb).c_str(),
		SLAVE_MAGIC, nullptr);
}
