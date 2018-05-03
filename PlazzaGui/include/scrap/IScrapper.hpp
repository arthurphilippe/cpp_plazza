/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** IScrapper
*/

#ifndef ISCRAPPER_HPP_
	#define ISCRAPPER_HPP_

	#include "Command.hpp"

namespace plazza {
	namespace scrap	{
		class IScrapper;
	}
}

class plazza::scrap::IScrapper {
public:
	virtual ~IScrapper() = default;
	virtual void run(const Command &) = 0;
	virtual std::ostream &serialise(std::ostream &) = 0;
};

std::ostream& operator<<(std::ostream &os, plazza::scrap::IScrapper &);
plazza::scrap::IScrapper
&operator>>(plazza::Command &, plazza::scrap::IScrapper &);

#endif /* !ISCRAPPER_HPP_ */
