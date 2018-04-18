/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ILink
*/

#include "ILink.hpp"

using Plazza::ILink;

std::ostream& operator<<(std::ostream& os, ILink &link)
{
	link.send(os);
	return os;
}

std::istream& operator>>(std::istream &in, ILink &link)
{
	return link.recive(in);
}
