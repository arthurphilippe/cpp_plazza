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

std::ostream& operator<<(std::ostream& os, const Plazza::Command &cmd)
{
	std::stringstream oss;
	oss << cmd.cmdId;
	oss << ",";

	oss << cmd.cmdInfoType;
	oss << ",";

	oss << cmd.cmdFileName.length();
	oss << ',';
	oss << cmd.cmdFileName;
	os << oss.str();
	return os;
}

std::istream& operator>>(std::istream &in, Plazza::Command &cmd)
{
	char separator;
	int tmp;
	std::string ramen;

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
