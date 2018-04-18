/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-Command
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "Command.hpp"
#include <sstream>

Test(Command, serialasation) {
	Plazza::Command cmd1;

	cmd1.cmdFileName = "toto";
	cmd1.cmdId = 42;
	cmd1.cmdInfoType = Plazza::Information::EMAIL_ADDRESS;

	std::stringstream ioss;
	ioss << cmd1;

	Plazza::Command cmd2;
	ioss >> cmd2;
	cr_assert_eq(cmd1.cmdId, cmd2.cmdId);
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_eq(cmd1.cmdInfoType, cmd2.cmdInfoType);
}
