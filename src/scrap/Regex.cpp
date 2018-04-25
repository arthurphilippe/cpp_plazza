/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Regex
*/

#include <fstream>
#include <regex>
#include <iostream>
#include <sstream>
#include "scrap/Regex.hpp"

using plazza::scrap::Regex;

Regex::Regex(const std::string &patnern)
	: _regex(patnern)
{}

void Regex::run(const Command &cmd)
{
	_cmd = cmd;
	std::ifstream file(cmd.cmdFileName);
	std::string line;

	if (!file)
		return;
	while (std::getline(file, line))
		processLine(line);
}

std::ostream &Regex::serialise(std::ostream &os)
{
	std::stringstream oss;
	oss << _cmd.cmdId;
	oss << " ";
	oss << _results.size();
	while (_results.size()) {
		oss << " ";
		auto &entry = _results.front();
		oss << entry.size();
		oss << ":";
		oss << entry;
		_results.pop();
	}
	// std::cout << oss.str() << std::endl;
	os << oss.str();
	return os;
}

void Regex::processLine(const std::string &line) noexcept
{
	auto matches_begin =
		std::sregex_iterator(line.begin(), line.end(), _regex);
	auto end = std::sregex_iterator();

	for (std::sregex_iterator i = matches_begin; i != end; ++i) {
		std::smatch match = *i;
		std::string match_str = match.str();
		_results.push(match_str);
	}
}
