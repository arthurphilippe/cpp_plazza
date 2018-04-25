/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-Regex
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "scrap/Regex.hpp"
#include "scrap/PhoneNumber.hpp"
#include "scrap/IpAddr.hpp"

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

	cmd.cmdFileName = "tests/phone_numbers.txt";
	interfacedScrapper->run(cmd);
	auto results = scrapper->results();
	cr_expect_eq(results.size(), 4);
	delete interfacedScrapper;
}

Test(IpAddr, 1_stringMatch) {
	plazza::scrap::IpAddr scrapper;

	scrapper.processLine("run ssh admin@216.58.198.195 to access the machine");
	auto results = scrapper.results();
	cr_expect_eq(results.size(), 1);
	cr_expect_str_eq(results.front().c_str(), "216.58.198.195");
}