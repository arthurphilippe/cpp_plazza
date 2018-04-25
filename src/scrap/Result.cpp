/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Result
*/

#include <iostream>
#include "scrap/Result.hpp"

using plazza::scrap::Result;

Result::Result()
	: _contents()
{}

Result::~Result()
{}

std::istream &Result::fill(std::istream &is) noexcept
{
	uint count;
	char separator;

	is >> _id;
	is >> count;
	for (uint i = 0; i < count; i++) {
		uint size;
		is >> size;
		is >> separator;
		std::vector<char> arr(size);
		is.read(arr.data(), size);

		std::string tmp(arr.data(), size);
		_contents.push(tmp);
	}
	return is;
}

std::ostream &Result::dump(std::ostream &os) noexcept
{
	while (_contents.size()) {
		os << _contents.front() << std::endl;
		_contents.pop();
	}
	return os;
}

std::istream &operator>>(std::istream &is, Result &res)
{
	return res.fill(is);
}

std::ostream &operator<<(std::ostream &os, Result &res)
{
	return res.dump(os);
}
