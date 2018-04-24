/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** PhoneNumber
*/

#ifndef PhoneNumber_HPP_
	#define PhoneNumber_HPP_

	#include "scrapping/Regex.hpp"

namespace Plazza::scrapping {
	class PhoneNumber;
}

class Plazza::scrapping::PhoneNumber : public Regex {
public:
	PhoneNumber()
		: Regex("([0-9]{10})")
	{}
	virtual ~PhoneNumber() override = default;
};

#endif /* !PhoneNumber_HPP_ */
