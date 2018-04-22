/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** main
*/

#include <iostream>

#include <iostream>
#include <regex>
#include <fstream>
#include <thread>

#include "Command.hpp"
#include "Information.hpp"
#include "ScopedLock.hpp"
#include "NamedPipe.hpp"


void print_block(int n, char c) {
	static std::mutex mtx;
	// critical section (exclusive access to std::cout signaled by locking mtx):
	Plazza::ScopedLock lock(mtx);
	for (int i=0; i<n; ++i) { std::cout << c; }
	std::cout << '\n';
}


std::string getfile()
{
	std::ifstream te("google.csv");
	std::stringstream buffer;
	buffer << te.rdbuf();
	std::string file(buffer.str());

//	std::cout << file << std::endl;
	return file;
}

static void fifo_master_create()
{
	try {
		Plazza::NamedPipe master(1, Plazza::NamedPipe::CREATE);
	} catch (std::exception &exept) {
		exept.what();
	}
}

static void fifo_slave_join()
{
	try {
		Plazza::NamedPipe master(1, Plazza::NamedPipe::JOIN);
	} catch (std::exception &exept) {
		exept.what();
	}
}

int main()
{
	// Plazza::NamedPipe master(1, Plazza::NamedPipe::CREATE);

	std::thread th1(fifo_master_create);
	std::thread th2(fifo_slave_join);

	th1.join();
	th2.join();
	std::regex r("([0-9]{10})");
 //   std::string file = getfile();

	std::string file("1234567890");
	std::smatch sm;

	if (regex_search(file, sm, r))
	{
		std::cout << "match" << std::endl;
		for (uint i=1; i<sm.size(); i++)
		{
			std::cout << sm[i] << std::endl;
		}
	}
}


// int main()
// {
// 	std::cout << "Heyyyy" << std::endl;
// }
