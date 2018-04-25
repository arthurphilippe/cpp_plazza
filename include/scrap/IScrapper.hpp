/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** IScrapper
*/

#ifndef ISCRAPPER_HPP_
	#define ISCRAPPER_HPP_

	#include "Command.hpp"

namespace plazza::scrap {
	class IScrapper;
}

class plazza::scrap::IScrapper {
public:
	virtual ~IScrapper() = default;
	virtual void run(const Command &) = 0;
	virtual std::ostream &serialise(std::ostream &) = 0;
};

#endif /* !ISCRAPPER_HPP_ */
