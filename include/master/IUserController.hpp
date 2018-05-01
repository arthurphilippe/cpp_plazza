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

namespace plazza {
	namespace master {
	class IUserController;
	}
}

class plazza::master::IUserController {
public:
	struct Progress {
		unsigned long int pending;
		unsigned long int sent;
		unsigned long int completed;
	};

	virtual ~IUserController() = default;
	virtual bool poll(std::queue<Command> &cmdQ) = 0;
	virtual void update(Progress) = 0;
};

#endif /* !IUSERCONTROLLER_HPP_ */
