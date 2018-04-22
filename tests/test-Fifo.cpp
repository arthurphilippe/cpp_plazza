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

static void fifo_master_create(Plazza::ILink **master, uint id)
{
	try {
		*master = new Plazza::NamedPipe(id, Plazza::NamedPipe::CREATE);
	} catch (Plazza::LinkExeption &exept) {
		*master = nullptr;
	}
}

static void fifo_slave_join(Plazza::ILink **slave, uint id)
{
	try {
		*slave = new Plazza::NamedPipe(id, Plazza::NamedPipe::JOIN);
	} catch (Plazza::LinkExeption &exept) {
		*slave = nullptr;
	}
}

Test(Fifo, TwoWayCreation) {
	Plazza::ILink *master = nullptr;
	Plazza::ILink *slave = nullptr;
	std::thread th1(fifo_master_create, &master, 1);
	std::thread th2(fifo_slave_join, &slave, 1);

	th1.join();
	th2.join();
	cr_assert(master);
	cr_assert(slave);
	delete master;
	delete slave;
}

static void fifo_send_test_msg(Plazza::ILink *pipe, const char *str)
{
	pipe->output() << str << std::endl;
}

static void fifo_rvc_test_msg(Plazza::ILink *pipe, const char *str)
{
	std::string toto;
	pipe->input() >> toto;
	cr_expect_str_eq(toto.c_str(), str);
}

Test(Fifo, SlaveBound) {
	Plazza::ILink *master = nullptr;
	Plazza::ILink *slave = nullptr;
	std::thread th1(fifo_master_create, &master, 2);
	std::thread th2(fifo_slave_join, &slave, 2);

	th1.join();
	th2.join();
	cr_assert(master);
	cr_assert(slave);
	std::thread th3(fifo_send_test_msg, master, "hey-there");
	std::thread th4(fifo_rvc_test_msg, slave, "hey-there");
	th3.join();
	th4.join();
	delete master;
	delete slave;
}
