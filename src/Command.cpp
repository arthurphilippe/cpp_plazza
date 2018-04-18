/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Command
*/

#include <iostream>
#include "Command.hpp"

std::ostream& operator<<(std::ostream& os, const Plazza::Command &cmd)
{
	// os << std::to_string(cmd.cmdId);
	os << cmd.cmdId;
	os << std::string(",");

	os << cmd.cmdInfoType;
	os << std::string(",");

	os << cmd.cmdFileName.length();
	os << cmd.cmdFileName;
	return os;
}

std::istream& operator>>(std::istream &in, Plazza::Command &cmd)
{
	char separator;
	int tmp;

	in >> cmd.cmdId;
	in >> separator;
	in >> tmp;
	cmd.cmdInfoType = static_cast<Plazza::Information>(tmp);
	return in;
}
