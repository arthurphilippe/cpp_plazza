/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Factory
*/

#include "scrap/Factory.hpp"
#include "scrap/PhoneNumber.hpp"
#include "scrap/IpAddr.hpp"
#include "scrap/EmailAddress.hpp"

using plazza::scrap::Factory;

plazza::scrap::IScrapper *Factory::create(const plazza::Information &info)
{
	IScrapper *scrapper;

	switch (info) {
	case PHONE_NUMBER:
		scrapper = new scrap::PhoneNumber();
		break;
	case IP_ADDRESS:
		scrapper = new scrap::IpAddr();
		break;
	case EMAIL_ADDRESS:
		scrapper = new scrap::EmailAddress();
		break;
	default:
		scrapper = nullptr;
		break;
	}
	return scrapper;
}
