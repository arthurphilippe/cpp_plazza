/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** RegexScrapper
*/

#ifndef RegexScrapper_HPP_
	#define RegexScrapper_HPP_

	#include <regex>
	#include <queue>
	#include "IScrapper.hpp"

namespace Plazza {
	class RegexScrapper;
}

class Plazza::RegexScrapper : public IScrapper {
	public:
		RegexScrapper(const std::string &partern);
		virtual ~RegexScrapper() noexcept = default;
		virtual void run(const Command &) override;
		virtual std::ostream &serialise(std::ostream &) override;
	protected:
		std::regex		_regex;
		Command			_cmd;
		std::queue<std::string>	_results;
};

#endif /* !RegexScrapper_HPP_ */
