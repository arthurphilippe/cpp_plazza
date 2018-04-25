/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** IScrapper
*/

#include "scrap/IScrapper.hpp"
using plazza::scrap::IScrapper;

std::ostream
&operator<<(std::ostream &os, IScrapper &scrp)
{
	scrp.serialise(os);
	return os;
}

IScrapper &operator>>(plazza::Command &command, IScrapper &scrp)
{
	scrp.run(command);
	return scrp;
}

