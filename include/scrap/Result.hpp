/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Result
*/

#ifndef RESULT_HPP_
	#define RESULT_HPP_

	#include <vector>
	#include "IScrapper.hpp"

namespace plazza {
	namespace scrap	{
		class Result;
	}
}

class plazza::scrap::Result {
public:
	Result();
	~Result();
	std::istream &fill(std::istream &) noexcept;
	std::ostream &dump(std::ostream &) noexcept;
	const std::vector<std::string> &contents() const noexcept
	{
		return _contents;
	}
	uint id() const noexcept
	{
		return _id;
	}

private:
	std::vector<std::string>	_contents;
	uint				_id;
};

std::istream &operator>>(std::istream &is, plazza::scrap::Result &res);
std::ostream &operator<<(std::ostream &os, plazza::scrap::Result &res);

#endif /* !RESULT_HPP_ */
