/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ILink
*/

#include <sstream>
#include "ILink.hpp"

using Plazza::ILink;

ILink &operator<<(ILink &out, const Plazza::Command &cmd)
{
	std::stringstream oss;
	oss << cmd;
	out.output() << oss.str() << std::endl;
	return out;
}

// std::ostream& operator<<(std::ostream& os, ILink &link)
// {
// 	link.send(os);
// 	return os;
// }

// std::istream& operator>>(std::istream &in, ILink &link)
// {
// 	return link.recive(in);
// }
