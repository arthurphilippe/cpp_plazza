/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-Fifo
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <thread>
#include "NamedPipe.hpp"
using namespace std::chrono_literals;

void fifo_master_create(Plazza::NamedPipe **master)
{
	try {
		*master = new Plazza::NamedPipe(1, Plazza::NamedPipe::CREATE);
	} catch (std::exception &exept) {
		*master = nullptr;
	}
}

void fifo_slave_join(Plazza::NamedPipe **slave)
{
	std::this_thread::sleep_for(10us);
	try {
		*slave = new Plazza::NamedPipe(1, Plazza::NamedPipe::JOIN);
	} catch (std::exception &exept) {
		*slave = nullptr;
	}
}

Test(Fifo, TwoWayCreation) {
	Plazza::NamedPipe *master;
	Plazza::NamedPipe *slave;
	std::thread th1(fifo_master_create, &master);
	std::thread th2(fifo_slave_join, &slave);

	th1.join();
	th2.join();
	cr_assert(master);
	cr_assert(slave);
	delete master;
	delete slave;
}
