/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ControllerFactory
*/

#ifndef CONTROLLERFACTORY_HPP_
	#define CONTROLLERFACTORY_HPP_

	#include "master/IUserController.hpp"
	#include "master/ControllerCLI.hpp"
	#include "master/DynamicObject.hpp"

namespace plazza::master {
	class ControllerFactory;
}

class plazza::master::ControllerFactory {
public:
	ControllerFactory() = delete;
	~ControllerFactory() = delete;
	static IUserController *create();
};

#endif /* !CONTROLLERFACTORY_HPP_ */
