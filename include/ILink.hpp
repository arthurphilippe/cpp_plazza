/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ILink
*/

#ifndef ILINK_HPP_
	#define ILINK_HPP_

	#include <iostream>
	#include <cstring>

namespace Plazza {
	class ILink;
	class LinkExeption;
	constexpr auto LINK_PREFIX = "plazza_";
}

class Plazza::ILink {
public:
	enum Mode {
		CREATE,
		JOIN,
	};
	virtual ~ILink() = default;
	virtual std::ostream &send(std::ostream &os) = 0;
	virtual std::istream &recive(std::istream &in) = 0;
};

class Plazza::LinkExeption : std::exception {
public:
	LinkExeption(std::string prefix, int err)
		: _what(prefix + std::strerror(err))
	{}
	const char *what() const noexcept
	{
		std::cerr << _what << std::endl;
		return _what.c_str();
	}
public:
	std::string _what;
};

std::ostream& operator<<(std::ostream& os, Plazza::ILink &link);
std::istream& operator>>(std::istream &in, Plazza::ILink &link);

#endif /* !ILINK_HPP_ */