/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-ControllerCLI
*/

#include <sstream>
#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "master/ControllerCLI.hpp"

Test(ControllerCLI, 1_someLines, .timeout = 2) {
	std::stringstream ioss;
	ioss << "toto" << std::endl;
	ioss << "toto" << std::endl;

	std::queue<plazza::Command> cmdQ;
	plazza::master::ControllerCLI ctrl(ioss);

	cr_assert_eq(ctrl.poll(cmdQ), true);
	cr_assert_eq(ctrl.poll(cmdQ), false);
}

Test(ControllerCLI, 2_eof, .timeout = 2) {
	std::stringstream ioss;
	ioss << plazza::master::CMD_EXIT << std::endl;
	ioss << "toto" << std::endl;
	ioss << "toto" << std::endl;

	std::queue<plazza::Command> cmdQ;
	plazza::master::ControllerCLI ctrl(ioss);

	cr_assert_eq(ctrl.poll(cmdQ), false);
}
