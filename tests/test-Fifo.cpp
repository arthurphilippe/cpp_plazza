/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-Fifo
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <thread>
#include <iostream>
#include "NamedPipe.hpp"

void fifo_master_create(Plazza::NamedPipe **master, uint id)
{
	try {
		*master = new Plazza::NamedPipe(id, Plazza::NamedPipe::CREATE);
	} catch (Plazza::LinkExeption &exept) {
		*master = nullptr;
	}
}

void fifo_slave_join(Plazza::NamedPipe **slave, uint id)
{
	try {
		*slave = new Plazza::NamedPipe(id, Plazza::NamedPipe::JOIN);
	} catch (Plazza::LinkExeption &exept) {
		*slave = nullptr;
	}
}

Test(Fifo, TwoWayCreation) {
	Plazza::NamedPipe *master = nullptr;
	Plazza::NamedPipe *slave = nullptr;
	std::thread th1(fifo_master_create, &master, 1);
	std::thread th2(fifo_slave_join, &slave, 1);

	th1.join();
	th2.join();
	cr_assert(master);
	cr_assert(slave);
	delete master;
	delete slave;
}

// Test(Fifo, TwoWayComm) {
// 	Plazza::NamedPipe *master = nullptr;
// 	Plazza::NamedPipe *slave = nullptr;
// 	std::thread th1(fifo_master_create, &master, 2);
// 	std::thread th2(fifo_slave_join, &slave, 2);

// 	th1.join();
// 	th2.join();
// 	cr_assert(master);
// 	cr_assert(slave);
// 	*master << "hey there";
// 	delete master;
// 	delete slave;
// }
