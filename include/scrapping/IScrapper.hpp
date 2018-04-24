/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** IScrapper
*/

#ifndef ISCRAPPER_HPP_
	#define ISCRAPPER_HPP_

	#include "Command.hpp"

namespace Plazza::scrapping {
	class IScrapper;
}

class Plazza::scrapping::IScrapper {
public:
	virtual ~IScrapper() = default;
	virtual void run(const Command &) = 0;
	virtual std::ostream &serialise(std::ostream &) = 0;
};

#endif /* !ISCRAPPER_HPP_ */
