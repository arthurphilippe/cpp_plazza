/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** test-ScopedLock
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <thread>
#include <chrono>
#include "ScopedLock.hpp"
using namespace std::chrono_literals;

std::mutex mtx;

void callLock(char *str)
{
	Plazza::ScopedLock lock(mtx);
	for (char c = '0'; c <= '9'; c++) {
		strncat(str, &c, 1);
		std::this_thread::sleep_for(10us);
	}
}

void callNoLock(char *str)
{
	for (char c = '0'; c <= '9'; c++) {
		strncat(str, &c, 1);
		std::this_thread::sleep_for(10us);
	}
}

Test(ScopedLock, orderInString) {
	char str[40];

	str[0] = 0;
	std::thread th1(callLock, str);
	std::thread th2(callLock, str);
	th1.join();
	th2.join();
	cr_assert_str_eq(str, "01234567890123456789");
}

Test(ScopedLock, noOrderInString) {
	char str[40];

	str[0] = 0;
	std::thread th1(callNoLock, str);
	std::thread th2(callNoLock, str);
	th1.join();
	th2.join();
	cr_assert_str_neq(str, "01234567890123456789");
}
