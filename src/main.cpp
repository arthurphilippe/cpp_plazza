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

static void fifo_master_create(Plazza::ILink **master, uint id)
{
	try {
		*master = new Plazza::NamedPipe(id, Plazza::NamedPipe::CREATE);
	} catch (Plazza::LinkExeption &exept) {
		exept.what();
		*master = nullptr;
		throw;
	}
}

static void fifo_slave_join(Plazza::ILink **slave, uint id)
{
	try {
		*slave = new Plazza::NamedPipe(id, Plazza::NamedPipe::JOIN);
	} catch (Plazza::LinkExeption &exept) {
		exept.what();
		*slave = nullptr;
		throw;
	}
}

static void cmd_send(Plazza::ILink *link, Plazza::Command *cmd)
{
	std::cout << "voiture" << std::endl;
	link->output() << *cmd;
}

static void cmd_rcvd(Plazza::ILink *link, Plazza::Command *cmd)
{
	std::cout << "autocar" << std::endl;
	link->input() >> *cmd;
}


int main()
{
	Plazza::ILink *master = nullptr;
	Plazza::ILink *slave = nullptr;
	std::thread th1(fifo_master_create, &master, 8);
	std::thread th2(fifo_slave_join, &slave, 8);
	th1.join();
	th2.join();

	Plazza::Command cmd1;
	cmd1.cmdFileName = "toto";
	cmd1.cmdId = 42;
	cmd1.cmdInfoType = Plazza::Information::EMAIL_ADDRESS;

	Plazza::Command cmd2;
	std::thread th3(cmd_send, master, &cmd1);
	std::thread th4(cmd_rcvd, slave, &cmd2);
	th3.join();
	th4.join();
	delete master;
	delete slave;
}

// int main()
// {
// 	std::regex r("([0-9]{10})");

// 	std::string file("1234567890");
// 	std::smatch sm;

// 	if (regex_search(file, sm, r))
// 	{
// 		std::cout << "match" << std::endl;
// 		for (uint i=1; i<sm.size(); i++)
// 		{
// 			std::cout << sm[i] << std::endl;
// 		}
// 	}
// }
