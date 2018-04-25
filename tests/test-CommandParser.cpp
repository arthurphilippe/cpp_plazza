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
	std::queue<plazza::Command> cmd;
	std::string line1("README.md ip_address");

	plazza::CommandParser kappa(cmd);
	kappa.ParseLine(line1);
	if (cmd.front().cmdFileName == "README.md")
		ret = true;
//	kappa.dump();
	std::cerr << cmd.front().cmdFileName << std::endl;
	cr_assert(ret);
}
