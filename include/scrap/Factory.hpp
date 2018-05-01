/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
	#define FACTORY_HPP_

	#include "IScrapper.hpp"
	#include "Information.hpp"

namespace plazza::scrap {
	class Factory;
}

class plazza::scrap::Factory {
public:
	Factory() = delete;
	~Factory() = delete;
	static IScrapper *create(const Information &);
};

#endif /* !FACTORY_HPP_ */
