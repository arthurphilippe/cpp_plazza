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

// 	plazza::CommandParser kappa(ke);
// 	if (true) {

// 	}
// 	cr_assert(true);
// }

Test(CommandParser, Real_IPAddress) {
	bool ret = false;
	std::queue<plazza::Command> cmdq;
	std::string line1("README.md ip_address");

	plazza::CommandParser kappa(cmdq);
	kappa.ParseLine(line1);
	cr_assert_str_eq(cmdq.front().cmdFileName.c_str(), "README.md");
}
