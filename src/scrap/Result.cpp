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
	if (is.eof())
		return is;
	for (uint i = 0; i < count; i++) {
		uint size;
		is >> size;
		is >> separator;
		std::vector<char> arr(size);
		is.read(arr.data(), size);

		std::string tmp(arr.data(), size);
		_contents.push_back(tmp);
	}
	return is;
}

std::ostream &Result::dump(std::ostream &os) noexcept
{
	for (const auto &elem : _contents) {
		if (&os != &std::cout)
			std::cout << elem << std::endl;
		os << elem << std::endl;
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
