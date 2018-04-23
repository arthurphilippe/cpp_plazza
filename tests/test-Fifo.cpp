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
#include "Command.hpp"

static void fifo_master_create(Plazza::ILink **master, uint id)
{
	try {
		*master = new Plazza::NamedPipe(id, Plazza::NamedPipe::CREATE);
	} catch (Plazza::LinkExeption &exept) {
		exept.what();
		*master = nullptr;
	}
}

static void fifo_slave_join(Plazza::ILink **slave, uint id)
{
	try {
		*slave = new Plazza::NamedPipe(id, Plazza::NamedPipe::JOIN);
	} catch (Plazza::LinkExeption &exept) {
		exept.what();
		*slave = nullptr;
	}
}

Test(Fifo, 1_TwoWayCreation) {
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

Test(Fifo, 2_SlaveBound) {
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

Test(Fifo, 3_MasterBound) {
	Plazza::ILink *master = nullptr;
	Plazza::ILink *slave = nullptr;
	std::thread th1(fifo_master_create, &master, 3);
	std::thread th2(fifo_slave_join, &slave, 3);

	th1.join();
	th2.join();
	cr_assert(master);
	cr_assert(slave);
	std::thread th3(fifo_send_test_msg, slave, "hey-there");
	std::thread th4(fifo_rvc_test_msg, master, "hey-there");
	th3.join();
	th4.join();
	delete master;
	delete slave;
}

Test(Fifo, 4_MasterBound) {
	Plazza::ILink *master = nullptr;
	Plazza::ILink *slave = nullptr;
	std::thread th1(fifo_master_create, &master, 4);
	std::thread th2(fifo_slave_join, &slave, 4);

	th1.join();
	th2.join();
	cr_assert(master);
	cr_assert(slave);
	std::thread th3(fifo_send_test_msg, slave, "hey-there");
	std::thread th4(fifo_rvc_test_msg, master, "hey-there");
	th3.join();
	th4.join();
	delete master;
	delete slave;
}

Test(Fifo, 5_MasterAndSlaveBound) {
	Plazza::ILink *master = nullptr;
	Plazza::ILink *slave = nullptr;
	std::thread th1(fifo_master_create, &master, 5);
	std::thread th2(fifo_slave_join, &slave, 5);

	th1.join();
	th2.join();
	cr_assert(master);
	cr_assert(slave);
	std::thread th3(fifo_send_test_msg, slave, "hey-there");
	std::thread th4(fifo_rvc_test_msg, master, "hey-there");
	th3.join();
	th4.join();
	std::thread th5(fifo_send_test_msg, master, "hey-there");
	std::thread th6(fifo_rvc_test_msg, slave, "hey-there");
	th5.join();
	th6.join();
	delete master;
	delete slave;
}

Test(Fifo, 6_TwoWayCreationErr) {
	Plazza::ILink *master = nullptr;
	Plazza::ILink *slave = nullptr;
	std::thread th1(fifo_master_create, &master, 6);
	std::thread th2(fifo_slave_join, &slave, 6);

	th1.join();
	th2.join();
	cr_assert(master);
	delete master;
	cr_assert(slave);

	cr_expect_throw(fifo_master_create(&master, 6), Plazza::LinkExeption);

	delete slave;
}

static void cmd_send(Plazza::ILink *link, Plazza::Command *cmd)
{
	*link << *cmd;
}

static void cmd_rcvd(Plazza::ILink *link, Plazza::Command *cmd)
{
	link->input() >> *cmd;
}

Test(Fifo, 8_SlaveBound) {
	Plazza::ILink *master = nullptr;
	Plazza::ILink *slave = nullptr;
	std::thread th1(fifo_master_create, &master, 8);
	std::thread th2(fifo_slave_join, &slave, 8);

	th1.join();
	th2.join();
	cr_assert(master);
	cr_assert(slave);

	Plazza::Command cmd1;
	cmd1.cmdFileName = "toto";
	cmd1.cmdId = 42;
	cmd1.cmdInfoType = Plazza::Information::EMAIL_ADDRESS;

	std::stringstream ioss;
	ioss << cmd1;

	std::thread th3(fifo_send_test_msg, master, ioss.str().c_str());
	std::thread th4(fifo_rvc_test_msg, slave, ioss.str().c_str());
	th3.join();
	th4.join();
	delete master;
	delete slave;
}


Test(Fifo, 9_CmdSerial) {
	Plazza::ILink *master = nullptr;
	Plazza::ILink *slave = nullptr;
	std::thread th1(fifo_master_create, &master, 9);
	std::thread th2(fifo_slave_join, &slave, 9);
	th1.join();
	th2.join();
	cr_assert(master);
	cr_assert(slave);

	Plazza::Command cmd1;
	cmd1.cmdFileName = "toto";
	cmd1.cmdId = 42;
	cmd1.cmdInfoType = Plazza::Information::EMAIL_ADDRESS;

	Plazza::Command cmd2;
	std::thread th3(cmd_send, master, &cmd1);
	std::thread th4(cmd_rcvd, slave, &cmd2);
	// std::thread th4(cmd_rcvd, slave, &cmd2);
	th3.join();
	th4.join();
	cr_expect_eq(cmd1.cmdId, cmd2.cmdId, "%d != %d\n", cmd1.cmdId, cmd2.cmdId);
	// cr_expect_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_expect_eq(cmd1.cmdInfoType, cmd2.cmdInfoType);
	// master->output() << cmd2;

	// Plazza::Command cmd3;
	// slave->input() >> cmd3;
	// cr_assert_eq(cmd1.cmdId, cmd3.cmdId);
	// cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd3.cmdFileName.c_str());
	// cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd3.cmdFileName.c_str());
	// cr_assert_eq(cmd1.cmdInfoType, cmd3.cmdInfoType);
}
