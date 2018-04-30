/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Command
*/

#include <iostream>
#include <vector>
#include <sstream>
#include "Command.hpp"

std::ostream& operator<<(std::ostream& os, const plazza::Command &cmd)
{
	os << cmd.cmdId;
	os << ",";

	os << cmd.cmdInfoType;
	os << ",";

	os << cmd.cmdFileName.length();
	os << ',';
	os << cmd.cmdFileName;
	os << std::endl;
	return os;
}

std::istream& operator>>(std::istream &in, plazza::Command &cmd)
{
	char separator;
	int tmp;

	in >> cmd.cmdId;
	in >> separator;

	in >> tmp;
	cmd.cmdInfoType = static_cast<plazza::Information>(tmp);
	in >> separator;

	in >> tmp;
	in >> separator;
	if (!in.eof() && tmp) {
		std::vector<char> arr(tmp);
		in.read(arr.data() , tmp);
		cmd.cmdFileName.assign(arr.data(), tmp);
	}
	return in;
}
