/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ControllerFactory
*/

#include "master/ControllerFactory.hpp"

using plazza::master::ControllerFactory;

plazza::master::IUserController *ControllerFactory::create()
{
	try {
		DynamicObject<IUserController>
		dynObj("PlazzaGui/libPlazzaGui.so.1.0.0");
		return dynObj.get();
	} catch (std::runtime_error &except) {
		return new ControllerCLI;
	}
	return nullptr;
}
