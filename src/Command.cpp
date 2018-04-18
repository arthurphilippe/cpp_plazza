/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Command
*/

#include <iostream>
#include <vector>
#include "Command.hpp"

std::ostream& operator<<(std::ostream& os, const Plazza::Command &cmd)
{
	// os << std::to_string(cmd.cmdId);
	os << cmd.cmdId;
	os << ",";

	os << cmd.cmdInfoType;
	os << ",";

	os << cmd.cmdFileName.length();
	os << ',';
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
	in >> separator;

	in >> tmp;
	in >> separator;
	if (tmp) {
		std::vector<char> arr(tmp);
		in.read(arr.data() , tmp);
		cmd.cmdFileName.assign(arr.data(), tmp);
	}
	return in;
}
