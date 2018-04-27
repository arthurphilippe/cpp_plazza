/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-Worker
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <thread>
#include "slave/Worker.hpp"
#include "scrap/IScrapper.hpp"
#include "scrap/Result.hpp"
#include "NamedPipe.hpp"
#include "Command.hpp"

using scrapperptr = std::unique_ptr<plazza::scrap::IScrapper>;

static void fifo_master_create(plazza::ILink **master, uint id)
{
	try {
		*master = new plazza::NamedPipe(id, plazza::NamedPipe::CREATE);
	} catch (plazza::LinkExeption &exept) {
		exept.what();
		*master = nullptr;
	}
}

static void worker_slave_create(plazza::slave::Worker **worker, uint id)
{
	*worker = new plazza::slave::Worker(id, 3);
}

Test(slaveWorker, 1_creation, .timeout = 2) {
	plazza::ILink *master = nullptr;
	plazza::slave::Worker *worker = nullptr;
	std::thread th1(fifo_master_create, &master, 11);
	std::thread th2(worker_slave_create, &worker, 11);

	th1.join();
	cr_assert(master);

	plazza::Command test;
	test.cmdFileName = "j'aime les pates!";
	test.cmdInfoType = plazza::Information::NONE;
	test.cmdId = 0;

	*master << test;

	th2.join();
}

Test(slaveWorker, 2_actualResults, .timeout = 2) {
	plazza::ILink *master = nullptr;
	plazza::slave::Worker *worker = nullptr;
	std::thread th1(fifo_master_create, &master, 12);
	std::thread th2(worker_slave_create, &worker, 12);

	th1.join();
	cr_assert(master);

	plazza::Command test;
	test.cmdFileName = "tests/4phone_numbers.txt";
	test.cmdInfoType = plazza::Information::PHONE_NUMBER;
	test.cmdId = 1;

	cr_log_info("sending first command...");
	*master << test;
	cr_log_info("sent!");

	plazza::scrap::Result res;
	cr_log_info("recovering results...");
	*master >> res;
	cr_log_info("recovered!");
	cr_assert_eq(res.contents().size(), 4);

	test.cmdFileName = "this is an stoping command.";
	test.cmdInfoType = plazza::Information::NONE;
	test.cmdId = 0;

	cr_log_info("sending terminating command...");
	*master << test;
	cr_log_info("sent!");
	th2.join();
	delete master;
	delete worker;
}
