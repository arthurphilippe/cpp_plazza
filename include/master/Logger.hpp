/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
	#define LOGGER_HPP_

	#include <unordered_map>
	#include <fstream>
	#include <vector>
	#include "Information.hpp"
	#include "scrap/Result.hpp"

namespace plazza::master {
	class Logger;
	constexpr auto DEFAULT_FILE_NAME("scrap_unsorted.log");
}

class plazza::master::Logger {
public:
	Logger();
	~Logger();

	void logResult(const Command &, scrap::Result &);

private:
	std::ofstream _phoneFile;
	std::ofstream _emailFile;
	std::ofstream _ipFile;
	std::ofstream _unsorted;

	std::ostream &_getfstream(plazza::Information);
};

#endif /* !LOGGER_HPP_ */
