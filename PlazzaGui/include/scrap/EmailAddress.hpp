/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** EmailAddress
*/

#ifndef EmailAddress_HPP_
	#define EmailAddress_HPP_

	#include "scrap/Regex.hpp"

namespace plazza::scrap {
	class EmailAddress;
	constexpr auto EMAIL_REGXP("\\b[_a-z0-9-]+(\\.[_a-z0-9-]+)\
*@[a-z0-9-]+\(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})\\b");
}

class plazza::scrap::EmailAddress : public Regex {
public:
	EmailAddress()
		: Regex(EMAIL_REGXP)
	{}
	virtual ~EmailAddress() override = default;
};

#endif /* !EmailAddress_HPP_ */
