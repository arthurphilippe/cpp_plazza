/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-Command
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <sstream>
#include "Command.hpp"

Test(Command, serialasation_basic) {
	plazza::Command cmd1;

	cmd1.cmdFileName = "toto";
	cmd1.cmdId = 42;
	cmd1.cmdInfoType = plazza::Information::EMAIL_ADDRESS;

	std::stringstream ioss;
	ioss << cmd1;

	plazza::Command cmd2;
	ioss >> cmd2;
	cr_assert_eq(cmd1.cmdId, cmd2.cmdId);
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_eq(cmd1.cmdInfoType, cmd2.cmdInfoType);
}

Test(Command, serialasation_double) {
	plazza::Command cmd1;

	cmd1.cmdFileName = "toto";
	cmd1.cmdId = 42;
	cmd1.cmdInfoType = plazza::Information::EMAIL_ADDRESS;

	std::stringstream ioss;
	ioss << cmd1;
	ioss << cmd1;

	plazza::Command cmd2;
	ioss >> cmd2;
	cr_assert_eq(cmd1.cmdId, cmd2.cmdId);
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_eq(cmd1.cmdInfoType, cmd2.cmdInfoType);

	plazza::Command cmd3;
	ioss >> cmd3;
	cr_assert_eq(cmd1.cmdId, cmd3.cmdId);
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd3.cmdFileName.c_str());
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd3.cmdFileName.c_str());
	cr_assert_eq(cmd1.cmdInfoType, cmd3.cmdInfoType);
}

Test(Command, serialasation_empty_name) {
	plazza::Command cmd1;

	cmd1.cmdFileName = "";
	cmd1.cmdId = 42;
	cmd1.cmdInfoType = plazza::Information::EMAIL_ADDRESS;

	std::stringstream ioss;
	ioss << cmd1;

	plazza::Command cmd2;
	ioss >> cmd2;
	cr_assert_eq(cmd1.cmdId, cmd2.cmdId);
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_eq(cmd1.cmdInfoType, cmd2.cmdInfoType);
}

Test(Command, serialasation_empty_id) {
	plazza::Command cmd1;

	cmd1.cmdFileName = "";
	cmd1.cmdId = 0;
	cmd1.cmdInfoType = plazza::Information::EMAIL_ADDRESS;

	std::stringstream ioss;
	ioss << cmd1;

	plazza::Command cmd2;
	ioss >> cmd2;
	cr_assert_eq(cmd1.cmdId, cmd2.cmdId);
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_eq(cmd1.cmdInfoType, cmd2.cmdInfoType);
	ioss << cmd2;

	plazza::Command cmd3;
	ioss >> cmd3;
	cr_assert_eq(cmd1.cmdId, cmd3.cmdId);
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd3.cmdFileName.c_str());
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd3.cmdFileName.c_str());
	cr_assert_eq(cmd1.cmdInfoType, cmd3.cmdInfoType);
	ioss >> cmd3;
}
