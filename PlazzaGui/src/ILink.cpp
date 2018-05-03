/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ILink
*/

#include <sstream>
#include "ILink.hpp"

using plazza::ILink;

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
