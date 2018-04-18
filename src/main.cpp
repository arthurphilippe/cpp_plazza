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

#include "Command.hpp"
#include "Information.hpp"

std::string getfile()
{
	std::ifstream te("google.csv");
	std::stringstream buffer;
	buffer << te.rdbuf();
	std::string file(buffer.str());

//	std::cout << file << std::endl;
	return file;
}

int main()
{
	std::ifstream test("test.serial");
	std::istream &test2(test);

	Plazza::Command cmd;

	test >> cmd;
	// cmd.cmdFileName = "toto";
	// cmd.cmdId = 1;
	// cmd.cmdInfoType = Plazza::PHONE_NUMBER;



	std::cout << cmd;
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
