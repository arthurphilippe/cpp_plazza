/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** IUserController
*/

#ifndef IUSERCONTROLLER_HPP_
	#define IUSERCONTROLLER_HPP_

	#include <queue>
	#include "Command.hpp"

namespace plazza::master {
	class IUserController;
}

class plazza::master::IUserController {
public:
	virtual ~IUserController() = default;
};

#endif /* !IUSERCONTROLLER_HPP_ */
