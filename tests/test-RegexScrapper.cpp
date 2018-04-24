/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-RegexScrapper
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "RegexScrapper.hpp"

Test(RegexScrapper, 1_match) {
	Plazza::RegexScrapper scrapper("([0-9]{10})");

	scrapper.processLine("Je mange un portavion au 0142424242 j'aimes les plantes.");
	auto result = scrapper.results().front();
	cr_assert_str_eq(result.c_str(), "0142424242");
}

Test(RegexScrapper, 2_matchNoSpacing) {
	Plazza::RegexScrapper scrapper("([0-9]{10})");

	scrapper.processLine("Je mange un portavion au0142424242j'aimes les plantes.");
	auto results = scrapper.results();
	cr_assert_eq(results.size(), 1);
	cr_assert_str_eq(results.front().c_str(), "0142424242");
	results.pop();
	cr_assert_eq(results.size(), 0);
}

Test(RegexScrapper, 3_matchEOL) {
	Plazza::RegexScrapper scrapper("([0-9]{10})");

	scrapper.processLine("Je mange un portavion au0142424242");
	auto results = scrapper.results();
	cr_assert_eq(results.size(), 1);
	cr_assert_str_eq(results.front().c_str(), "0142424242");
	results.pop();
	cr_assert_eq(results.size(), 0);
}

Test(RegexScrapper, 4_2matches) {
	Plazza::RegexScrapper scrapper("([0-9]{10})");

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

Test(RegexScapper, 5_multiplesMatches) {
	Plazza::RegexScrapper scrapper("([0-9]{10})");

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

Test(RegexScapper, 6_fileMatches) {
	auto *scrapper = new Plazza::RegexScrapper("([0-9]{10})");
	Plazza::IScrapper *interfacedScrapper = scrapper;
	Plazza::Command cmd;

	cmd.cmdFileName = "tests/phone_numbers.txt";
	interfacedScrapper->run(cmd);
	auto results = scrapper->results();
	cr_expect_eq(results.size(), 4);
	delete interfacedScrapper;
}
