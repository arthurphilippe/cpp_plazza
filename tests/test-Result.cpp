/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-Result
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "scrap/Regex.hpp"
#include "scrap/PhoneNumber.hpp"
#include "scrap/IpAddr.hpp"
#include "scrap/EmailAddress.hpp"
#include "scrap/Result.hpp"
#include "iostream"

using plazza::scrap::Regex;
using plazza::scrap::Result;

Test(Result, 1_completeTest) {
	auto *scrapper = new plazza::scrap::PhoneNumber();
	plazza::scrap::IScrapper *interfacedScrapper = scrapper;
	plazza::Command cmd;

	cmd.cmdFileName = "tests/4phone_numbers.txt";
	cmd.cmdId = 42;
	cmd.cmdInfoType = plazza::PHONE_NUMBER;
	cmd >> *interfacedScrapper;
	auto results = scrapper->results();
	cr_expect_eq(results.size(), 4);
	std::stringstream ioss;
	interfacedScrapper->serialise(ioss);

	Result res;
	res.fill(ioss);
	auto resultqueue = res.contents();
	cr_assert_eq(resultqueue.size(), 4);
	cr_assert_str_eq(resultqueue.front().c_str(), "0123232425");
	resultqueue.pop();
	cr_assert_eq(resultqueue.size(), 3);
	cr_assert_str_eq(resultqueue.front().c_str(), "0942424242");
	resultqueue.pop();
	cr_assert_eq(resultqueue.size(), 2);
	cr_assert_str_eq(resultqueue.front().c_str(), "0838383838");
	resultqueue.pop();
	cr_assert_eq(resultqueue.size(), 1);
	cr_assert_str_eq(resultqueue.front().c_str(), "0484545812");
	resultqueue.pop();
}

Test(Result, 2_serialisation) {
	auto *scrapper = new plazza::scrap::PhoneNumber();
	plazza::scrap::IScrapper *interfacedScrapper = scrapper;
	plazza::Command cmd;

	cmd.cmdFileName = "tests/4phone_numbers.txt";
	cmd.cmdId = 42;
	cmd.cmdInfoType = plazza::PHONE_NUMBER;
	cmd >> *interfacedScrapper;
	auto results = scrapper->results();
	cr_expect_eq(results.size(), 4);
	std::stringstream ioss;
	interfacedScrapper->serialise(ioss);

	Result res;
	res.fill(ioss);
	std::stringstream oss;
	oss << res;
	const std::string &ref(oss.str());
	cr_assert_str_eq(ref.c_str(), "0123232425\n0942424242\n0838383838\n0484545812\n");
}
