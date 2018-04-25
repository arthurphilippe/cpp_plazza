/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Regex
*/

#ifndef Regex_HPP_
	#define Regex_HPP_

	#include <regex>
	#include <queue>
	#include "IScrapper.hpp"

namespace plazza::scrap {
	class Regex;
}

class plazza::scrap::Regex : public IScrapper {
public:
	Regex(const std::string &partern);
	virtual ~Regex() noexcept = default;
	virtual void run(const Command &) override;
	virtual std::ostream &serialise(std::ostream &) override;
	void processLine(const std::string &line) noexcept;
	const std::queue<std::string> &results() const noexcept
	{
		return _results;
	}
protected:
	std::regex		_regex;
	Command			_cmd;
	std::queue<std::string>	_results;
};

#endif /* !Regex_HPP_ */
