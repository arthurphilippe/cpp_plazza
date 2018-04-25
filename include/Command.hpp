/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Command
*/

#ifndef COMMAND_HPP_
	#define COMMAND_HPP_

	#include <string>
	#include "Information.hpp"

namespace plazza {
	struct Command;
}

struct plazza::Command {
	std::string cmdFileName;
	enum Information cmdInfoType;
	uint cmdId;
};

std::ostream& operator<<(std::ostream& os, const plazza::Command &cmd);
std::istream& operator>>(std::istream &in, plazza::Command &cmd);

#endif /* !COMMAND_HPP_ */
