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

Test(Command, serialasation_double) {
	Plazza::Command cmd1;

	cmd1.cmdFileName = "toto";
	cmd1.cmdId = 42;
	cmd1.cmdInfoType = Plazza::Information::EMAIL_ADDRESS;

	std::stringstream ioss;
	ioss << cmd1;
	ioss << cmd1;

	Plazza::Command cmd2;
	ioss >> cmd2;
	cr_assert_eq(cmd1.cmdId, cmd2.cmdId);
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_eq(cmd1.cmdInfoType, cmd2.cmdInfoType);

	Plazza::Command cmd3;
	ioss >> cmd3;
	cr_assert_eq(cmd1.cmdId, cmd3.cmdId);
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd3.cmdFileName.c_str());
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd3.cmdFileName.c_str());
	cr_assert_eq(cmd1.cmdInfoType, cmd3.cmdInfoType);
}

Test(Command, serialasation_empty_name) {
	Plazza::Command cmd1;

	cmd1.cmdFileName = "";
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

Test(Command, serialasation_empty_id) {
	Plazza::Command cmd1;

	cmd1.cmdFileName = "";
	cmd1.cmdId = 0;
	cmd1.cmdInfoType = Plazza::Information::EMAIL_ADDRESS;

	std::stringstream ioss;
	ioss << cmd1;

	Plazza::Command cmd2;
	ioss >> cmd2;
	cr_assert_eq(cmd1.cmdId, cmd2.cmdId);
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd2.cmdFileName.c_str());
	cr_assert_eq(cmd1.cmdInfoType, cmd2.cmdInfoType);
	ioss << cmd2;

	Plazza::Command cmd3;
	ioss >> cmd3;
	cr_assert_eq(cmd1.cmdId, cmd3.cmdId);
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd3.cmdFileName.c_str());
	cr_assert_str_eq(cmd1.cmdFileName.c_str(), cmd3.cmdFileName.c_str());
	cr_assert_eq(cmd1.cmdInfoType, cmd3.cmdInfoType);
	ioss >> cmd3;
}
