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

Plazza::LinkExeption::LinkExeption(std::string prefix, int err)
	: _what(prefix + std::strerror(err))
{}

Plazza::LinkExeption::LinkExeption(std::string prefix)
	: _what(prefix)
{}

const char *Plazza::LinkExeption::what() const noexcept
{
	std::cerr << _what << std::endl;
	return _what.c_str();
}
