/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-ControllerCLI
*/

#include <sstream>
#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "master/ControllerCLI.hpp"

Test(ControllerCLI, 1_someLines, .timeout = 2) {
	cr_redirect_stderr();
	cr_redirect_stdout();
	std::stringstream ioss;
	ioss << "toto" << std::endl;
	ioss << "toto" << std::endl;

	std::queue<plazza::Command> cmdQ;
	plazza::master::ControllerCLI ctrl(ioss);

	cr_assert_eq(ctrl.poll(cmdQ), true);
	cr_assert_eq(ctrl.poll(cmdQ), false);
}

Test(ControllerCLI, 2_eof, .timeout = 2) {
	cr_redirect_stderr();
	cr_redirect_stdout();
	std::stringstream ioss;
	ioss << plazza::master::CMD_EXIT << std::endl;
	ioss << "toto" << std::endl;
	ioss << "toto" << std::endl;

	std::queue<plazza::Command> cmdQ;
	plazza::master::ControllerCLI ctrl(ioss);

	cr_assert_eq(ctrl.poll(cmdQ), false);
}

Test(ControllerCLI, 3_actualCommand, .timeout = 2) {
	cr_redirect_stderr();
	cr_redirect_stdout();
	std::stringstream ioss;
	ioss << ".editorconfig IP_ADDRESS" << std::endl;

	std::queue<plazza::Command> cmdQ;

	plazza::master::ControllerCLI ctrl(ioss);
	cr_assert_eq(ctrl.poll(cmdQ), true);
	cr_assert_eq(ctrl.poll(cmdQ), false);
	cr_assert_eq(cmdQ.size(), 1);
}

Test(ControllerCLI, 4_actualsCommand, .timeout = 2) {
	cr_redirect_stderr();
	cr_redirect_stdout();
	std::stringstream ioss;
	ioss << ".editorconfig .gitignore IP_ADDRESS" << std::endl;
	ioss << ".editorconfig .gitignore PHONE_NUMBER" << std::endl;
	ioss << "Makefile EMAIL_ADDRESS" << std::endl;

	std::queue<plazza::Command> cmdQ;

	plazza::master::ControllerCLI ctrl(ioss);
	cr_assert_eq(ctrl.poll(cmdQ), true);
	cr_assert_eq(ctrl.poll(cmdQ), false);
	cr_assert_eq(cmdQ.size(), 5);
}
