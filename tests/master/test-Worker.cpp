/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-Worker
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
#include "NamedPipe.hpp"
#include "scrap/PhoneNumber.hpp"
#include "master/Worker.hpp"
#include "scrap/Result.hpp"

Test(masterWorker, fork, .timeout = 1) {
	pid_t pid = fork();

	if (!pid) {
		exit(0);
	} else if (pid > 0) {
		cr_assert(1);
	} else {
		cr_assert_fail();
	}
}

static void create_worker(plazza::master::Worker **worker)
{
	*worker = new plazza::master::Worker(0, 0);
}

static void delete_worker(plazza::master::Worker *worker)
{
	delete worker;
}

Test(masterWorker, results, .timeout = 2) {
	// plazza::ILink *slave = nullptr;
	// std::thread th1(fifo_slave_join, &slave, 1);
	plazza::master::Worker *work;
	std::thread th1(create_worker, &work);
	plazza::NamedPipe *slave;
	slave = new plazza::NamedPipe(0, plazza::NamedPipe::JOIN);

	th1.join();
	if (!work) {
		cr_log_error("failed to create worker");
	}
	if (!slave) {
		cr_log_error("failed to create slave");
	}
	cr_assert(work);
	cr_assert(slave);

	auto *scrapper = new plazza::scrap::PhoneNumber();
	plazza::scrap::IScrapper *interfacedScrapper = scrapper;
	plazza::Command cmd;

	cmd.cmdFileName = "tests/4phone_numbers.txt";
	cmd.cmdId = 42;
	cmd.cmdInfoType = plazza::PHONE_NUMBER;
	cmd >> *interfacedScrapper;
	auto results = scrapper->results();
	cr_expect_eq(results.size(), 4);

	*slave << *scrapper;

	std::vector<plazza::scrap::Result> resultsvec;
	cr_log_info("about to gather results");
	while (!resultsvec.size()) {
		cr_log_info("results loop");
		std::this_thread::sleep_for(std::chrono::microseconds(10));
		work->fillResults(resultsvec);
	}
	cr_log_info("got results");

	cr_assert_eq(resultsvec.size(), 1, "got %d instead of %d", resultsvec.size(), 1);

	cr_log_info("deleting scapper");
	delete scrapper;
	cr_log_info("deleting worker");
	std::thread th2(delete_worker, work);
	cr_log_info("deleting slave");
	delete slave;
	th2.join();
	cr_log_info("finished");
}
