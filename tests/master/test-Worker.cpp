/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-Worker
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <sys/types.h>
#include <unistd.h>

Test(masterWorker, fork, .timeout = 1) {
	pid_t pid = fork();

	if (!pid) {
		exit(0);
	} else if (pid > 0) {
		cr_assert(1);
	} else {
		cr_assert_fail();
	}
}
