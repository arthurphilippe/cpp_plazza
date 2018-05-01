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
	auto copieres = resultqueue;
	cr_assert_str_eq(resultqueue[0].c_str(), "0123232425");
	cr_assert_str_eq(resultqueue[1].c_str(), "0942424242");
	cr_assert_str_eq(resultqueue[2].c_str(), "0838383838");
	cr_assert_str_eq(resultqueue[3].c_str(), "0484545812");
	cr_assert_str_eq(copieres[0].c_str(), "0123232425");
	cr_assert_str_eq(copieres[1].c_str(), "0942424242");
	cr_assert_str_eq(copieres[2].c_str(), "0838383838");
	cr_assert_str_eq(copieres[3].c_str(), "0484545812");
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
