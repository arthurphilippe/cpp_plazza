/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** PhoneNumber
*/

#ifndef PhoneNumber_HPP_
	#define PhoneNumber_HPP_

	#include "scrap/Regex.hpp"

namespace plazza::scrap {
	class PhoneNumber;
}

class plazza::scrap::PhoneNumber : public Regex {
public:
	PhoneNumber()
		: Regex("(?:(?:\\+|00)33|0)\\s*[1-9](?:[\\s.-]*\\d{2}){4}")
	{}
	virtual ~PhoneNumber() override = default;
};

#endif /* !PhoneNumber_HPP_ */
