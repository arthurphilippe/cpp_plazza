/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** CommandParser
*/

#include <iostream>
#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "CommandParser.hpp"

// Test(CommandParser, Default) {
// 	bool ret = false;
// 	std::queue<plazza::Command> ke;

// 	plazza::CommandParser parser(ke);
// 	if (true) {

// 	}
// 	cr_assert(true);
// }

Test(CommandParser, OneIPAddress) {
	std::queue<plazza::Command> cmdq;
	std::string line1("README.md ip_address");

	plazza::CommandParser parser(cmdq);
	parser.ParseLine(line1);
	cr_assert_str_eq(cmdq.front().cmdFileName.c_str(), "README.md");
}

Test(CommandParser, TwoIPAddresses) {
	std::queue<plazza::Command> cmdq;
	std::string line1("README.md .gitignore ip_address");

	plazza::CommandParser parser(cmdq);
	parser.ParseLine(line1);
	cr_expect_eq(cmdq.size(), 2, "Size was supposed to be %d but is %d", 2, cmdq.size());
	cr_assert_str_eq(cmdq.front().cmdFileName.c_str(), "README.md");
	cmdq.pop();
	cr_assert_str_eq(cmdq.front().cmdFileName.c_str(), ".gitignore");
}

Test(CommandParser, TwoIPAddressesAndErr) {
	cr_redirect_stderr();
	std::queue<plazza::Command> cmdq;
	std::string line1("README.md IDONOTEXIST .gitignore ip_address");

	plazza::CommandParser parser(cmdq);
	parser.ParseLine(line1);
	cr_expect_eq(cmdq.size(), 2, "Size was supposed to be %d but is %d", 2, cmdq.size());
	cr_assert_str_eq(cmdq.front().cmdFileName.c_str(), "README.md");
	cmdq.pop();
	cr_assert_str_eq(cmdq.front().cmdFileName.c_str(), ".gitignore");
}

Test(CommandParser, NothingExists) {
	cr_redirect_stderr();
	std::queue<plazza::Command> cmdq;
	std::string line1("READqfze.md IDONOTEXIST .dgrgitignore ip_address");

	plazza::CommandParser parser(cmdq);
	parser.ParseLine(line1);
	cr_expect_eq(cmdq.size(), 0, "Size was supposed to be %d but is %d", 0, cmdq.size());
}

Test(CommandParser, WrongType) {
	cr_redirect_stderr();
	std::queue<plazza::Command> cmdq;
	std::string line1("README.md .gitignore platypus");

	plazza::CommandParser parser(cmdq);
	parser.ParseLine(line1);
	cr_expect_eq(cmdq.size(), 0, "Size was supposed to be %d but is %d", 0, cmdq.size());
}
