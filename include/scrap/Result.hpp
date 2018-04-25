/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Result
*/

#ifndef RESULT_HPP_
	#define RESULT_HPP_

	#include <queue>
	#include "IScrapper.hpp"

namespace plazza::scrap {
	class Result;
}

class plazza::scrap::Result {
public:
	Result();
	~Result();
	std::istream &fill(std::istream &) noexcept;
	std::ostream &dump(std::ostream &) noexcept;
	const std::queue<std::string> &contents() const noexcept
	{
		return _contents;
	}
	uint id() const noexcept
	{
		return _id;
	}

private:
	std::queue<std::string> _contents;
	uint _id;
};

#endif /* !RESULT_HPP_ */
