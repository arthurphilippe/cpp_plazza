/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Worker
*/

#include "slave/Worker.hpp"
#include "NamedPipe.hpp"

using plazza::slave::Worker;

Worker::Worker(unsigned int id, unsigned int threadNb)
	: _id(id), _threadNb(threadNb),
	_link(new plazza::NamedPipe(_id, NamedPipe::JOIN))
{
	(void) _threadNb;
}

Worker::~Worker()
{}

void Worker::loop()
{}
