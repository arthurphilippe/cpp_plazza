/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-Fifo
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "NamedPipe.hpp"

Test(Fifo, 2way) {
	try {
		Plazza::NamedPipe master(1, Plazza::NamedPipe::CREATE);
		// Plazza::NamedPipe slave(1, Plazza::NamedPipe::JOIN);
	} catch (std::exception &exept) {
		exept.what();
		cr_assert_fail();
	}
}
