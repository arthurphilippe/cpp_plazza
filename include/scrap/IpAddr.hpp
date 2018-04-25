/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** IpAddr
*/

#ifndef IpAddr_HPP_
	#define IpAddr_HPP_

	#include "scrap/Regex.hpp"

namespace plazza::scrap {
	class IpAddr;
	constexpr auto IP_REGXP = "\\b(?:(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\b";
}

class plazza::scrap::IpAddr : public Regex {
public:
	IpAddr()
		: Regex(IP_REGXP)
	{}
	virtual ~IpAddr() override = default;
};

#endif /* !IpAddr_HPP_ */
