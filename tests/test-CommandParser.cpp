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

Test(CommandParser, StringCleanning) {
	bool ret = false;
	std::queue<Plazza::Command> ke;
	std::string line("     PO      TA       TO         ");

	Plazza::CommandParser kappa(ke);
	line = kappa.ParseLine(line);
	cr_assert_str_eq(line.c_str(), "PO TA TO");
}
