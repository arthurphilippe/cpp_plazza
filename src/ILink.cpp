/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ILink
*/

#include <sstream>
#include "ILink.hpp"

using plazza::ILink;

ILink &operator<<(ILink &out, const plazza::Command &cmd)
{
	out.output() << cmd << std::endl;
	return out;
}

ILink &operator<<(ILink &out, plazza::scrap::IScrapper &scrp)
{
	out.output() << scrp << std::endl;
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

plazza::LinkExeption::LinkExeption(std::string prefix, int err)
	: _what(prefix + std::strerror(err))
{}

plazza::LinkExeption::LinkExeption(std::string prefix)
	: _what(prefix)
{}

const char *plazza::LinkExeption::what() const noexcept
{
	std::cerr << _what << std::endl;
	return _what.c_str();
}
