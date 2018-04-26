/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-Regex
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <thread>
#include "scrap/Regex.hpp"
#include "scrap/PhoneNumber.hpp"
#include "scrap/IpAddr.hpp"
#include "scrap/EmailAddress.hpp"
#include "NamedPipe.hpp"

using plazza::scrap::Regex;

Test(Regex, 1_match) {
	Regex scrapper("([0-9]{10})");

	scrapper.processLine("Je mange un portavion au 0142424242 j'aimes les plantes.");
	auto result = scrapper.results().front();
	cr_assert_str_eq(result.c_str(), "0142424242");
}

Test(Regex, 2_matchNoSpacing) {
	Regex scrapper("([0-9]{10})");

	scrapper.processLine("Je mange un portavion au0142424242j'aimes les plantes.");
	auto results = scrapper.results();
	cr_assert_eq(results.size(), 1);
	cr_assert_str_eq(results.front().c_str(), "0142424242");
	results.pop();
	cr_assert_eq(results.size(), 0);
}

Test(Regex, 3_matchEOL) {
	Regex scrapper("([0-9]{10})");

	scrapper.processLine("Je mange un portavion au0142424242");
	auto results = scrapper.results();
	cr_assert_eq(results.size(), 1);
	cr_assert_str_eq(results.front().c_str(), "0142424242");
	results.pop();
	cr_assert_eq(results.size(), 0);
}

Test(Regex, 4_2matches) {
	Regex scrapper("([0-9]{10})");

	scrapper.processLine("Je mange un portavion au0142424242 kappa 0632361153");
	auto results = scrapper.results();
	cr_assert_eq(results.size(), 2);
	cr_assert_str_eq(results.front().c_str(), "0142424242");
	results.pop();
	cr_assert_eq(results.size(), 1);
	cr_assert_str_eq(results.front().c_str(), "0632361153");
	results.pop();
	cr_assert_eq(results.size(), 0);
}

Test(Regex, 5_multiplesMatches) {
	Regex scrapper("([0-9]{10})");

	scrapper.processLine("Je mange un portavion au 0142424242 j'aimes les plantes.");
	auto result = scrapper.results().front();
	cr_assert_str_eq(result.c_str(), "0142424242");
	scrapper.processLine("0176767676 Je mange un portavion au 0142424242 j'aimes les plantes. 0987678765");
	cr_assert_eq(scrapper.results().size(), std::size_t(4), "expectd %ld and got %ld.", std::size_t(4), scrapper.results().size());
	auto results = scrapper.results();
	cr_assert_str_eq(results.front().c_str(), "0142424242");
	results.pop();
	cr_expect_eq(results.size(), 3);
	cr_expect_str_eq(results.front().c_str(), "0176767676");
	results.pop();
	cr_expect_eq(results.size(), 2);
	cr_expect_str_eq(results.front().c_str(), "0142424242");
	results.pop();
	cr_expect_eq(results.size(), 1);
	cr_expect_str_eq(results.front().c_str(), "0987678765");
	results.pop();
	cr_expect_eq(results.size(), 0);
}

Test(Regex, 6_fileMatches) {
	auto *scrapper = new plazza::scrap::PhoneNumber();
	plazza::scrap::IScrapper *interfacedScrapper = scrapper;
	plazza::Command cmd;

	cmd.cmdFileName = "tests/4phone_numbers.txt";
	interfacedScrapper->run(cmd);
	auto results = scrapper->results();
	cr_expect_eq(results.size(), 4);
	delete interfacedScrapper;
}

Test(Regex, 7_serialise) {
	auto *scrapper = new plazza::scrap::PhoneNumber();
	plazza::scrap::IScrapper *interfacedScrapper = scrapper;
	plazza::Command cmd;

	cmd.cmdFileName = "tests/4phone_numbers.txt";
	cmd.cmdId = 42;
	cmd.cmdInfoType = plazza::PHONE_NUMBER;
	cmd >> *interfacedScrapper;
	auto results = scrapper->results();
	cr_expect_eq(results.size(), 4);
	std::stringstream oss;
	interfacedScrapper->serialise(oss);

	uint id;
	int tmp;

	oss >> id;
	cr_assert_eq(id, cmd.cmdId);
	oss >> tmp;
	cr_assert_eq(tmp, results.size());
	oss >> tmp;
	cr_assert_eq(tmp, 10);
	delete interfacedScrapper;
}

Test(IpAddr, 1_stringMatch) {
	plazza::scrap::IpAddr scrapper;

	scrapper.processLine("run ssh admin@216.58.198.195 to access the machine");
	auto results = scrapper.results();
	cr_expect_eq(results.size(), 1);
	cr_expect_str_eq(results.front().c_str(), "216.58.198.195");
}

Test(IpAddr, 2_stringMatches) {
	plazza::scrap::IpAddr scrapper;

	scrapper.processLine("run ssh admin@216.58.198.195 to access the machine but try to ping it before 216.51.198.195");
	auto results = scrapper.results();
	cr_expect_eq(results.size(), 2);
	cr_expect_str_eq(results.front().c_str(), "216.58.198.195");
	results.pop();
	cr_expect_eq(results.size(), 1);
	cr_expect_str_eq(results.front().c_str(), "216.51.198.195");
	results.pop();
}

Test(EmailAddress, 1_stringMatch) {
	plazza::scrap::EmailAddress scrapper;

	scrapper.processLine("send a mail at paris-tech2@epitech.eu kek");
	auto results = scrapper.results();
	cr_expect_eq(results.size(), 1);
	cr_expect_str_eq(results.front().c_str(), "paris-tech2@epitech.eu");
}

Test(EmailAddress, 2_stringMatches) {
	plazza::scrap::EmailAddress scrapper;

	scrapper.processLine("send a mail at paris-tech2@epitech.eu kek\
or at pere-noel@epita.net");
	auto results = scrapper.results();
	cr_expect_eq(results.size(), 2);
	cr_expect_str_eq(results.front().c_str(), "paris-tech2@epitech.eu");
	results.pop();
	cr_expect_eq(results.size(), 1);
	cr_expect_str_eq(results.front().c_str(), "pere-noel@epita.net");
	results.pop();
}

static void fifo_master_create(plazza::ILink **master, uint id)
{
	try {
		*master = new plazza::NamedPipe(id, plazza::NamedPipe::CREATE);
	} catch (plazza::LinkExeption &exept) {
		exept.what();
		*master = nullptr;
	}
}

static void fifo_slave_join(plazza::ILink **slave, uint id)
{
	try {
		*slave = new plazza::NamedPipe(id, plazza::NamedPipe::JOIN);
	} catch (plazza::LinkExeption &exept) {
		exept.what();
		*slave = nullptr;
	}
}

Test(Regex, 8_sendOnPipe) {
	plazza::ILink *master = nullptr;
	plazza::ILink *slave = nullptr;
	std::thread th1(fifo_master_create, &master, 9);
	std::thread th2(fifo_slave_join, &slave, 9);
	th1.join();
	th2.join();
	cr_assert(master);
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
	*master << *interfacedScrapper;
	// interfacedScrapper->serialise(oss);

	uint id;
	int tmp;

	slave->input() >> id;
	cr_assert_eq(id, cmd.cmdId);
	slave->input() >> tmp;
	cr_assert_eq(tmp, results.size());
	slave->input() >> tmp;
	cr_assert_eq(tmp, 10);
	delete interfacedScrapper;

}
