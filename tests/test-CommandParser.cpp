/*
** EPITECH PROJECT, 2018
** Plazza
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
// 	std::queue<Plazza::Command> ke;

// 	Plazza::CommandParser kappa(ke);
// 	if (true) {

// 	}
// 	cr_assert(true);
// }

Test(CommandParser, Real_IPAddress) {
	bool ret = false;
	std::queue<Plazza::Command> cmd;
	std::string line1("README.md ip_address");

	Plazza::CommandParser kappa(cmd);
	kappa.ParseLine(line1);
	if (cmd.front().cmdFileName == "README.md")
		ret = true;
//	kappa.dump();
	std::cerr << cmd.front().cmdFileName << std::endl;
	cr_assert(ret);
}
