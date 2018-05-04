/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** main
*/

#include "Startup.hpp"

int main(int ac, char **av)
{
	plazza::Startup startpoint(ac, av);

	return startpoint.launch();
}
