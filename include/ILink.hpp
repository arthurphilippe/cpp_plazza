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
	#include "Command.hpp"
	#include "scrap/IScrapper.hpp"

namespace plazza {
	class ILink;
	class LinkExeption;
	constexpr auto LINK_PREFIX = "plazza_";
}

class plazza::ILink {
public:
	enum Mode {
		CREATE,
		JOIN,
		NONE,
	};
	virtual ~ILink() = default;
	virtual std::ostream &output() = 0;
	virtual std::istream &input() = 0;
	virtual bool eof() const noexcept = 0;
};

class plazza::LinkExeption : std::exception {
public:
	LinkExeption(std::string prefix, int err);
	LinkExeption(std::string prefix);
	const char *what() const noexcept;
public:
	std::string _what;
};

std::ostream& operator<<(std::ostream &os, plazza::ILink &link);
std::istream& operator>>(std::istream &in, plazza::ILink &link);

template<typename T>
plazza::ILink &operator<<(plazza::ILink &out, const T &var)
{
	out.output() << var;
	return out;
}

template<typename T>
plazza::ILink &operator<<(plazza::ILink &out, T &var)
{
	out.output() << var;
	return out;
}

template<typename T>
plazza::ILink &operator>>(plazza::ILink &in, T &var)
{
	in.input() >> var;
	return in;
}

#endif /* !ILINK_HPP_ */
