/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Launch
*/

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
