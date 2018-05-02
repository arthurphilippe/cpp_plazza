/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Logger
*/

#include "master/Logger.hpp"

using plazza::master::Logger;

Logger::Logger()
	: _phoneFile("scrap_phone_numbers.log"),
	_emailFile("scrap_email_addresses.log"),
	_ipFile("scrap_ip_addresses.log"),
	_unsorted(DEFAULT_FILE_NAME)
{}

Logger::~Logger()
{}

void
Logger::logResult(const plazza::Command &cmd, plazza::scrap::Result &res)
{
	auto &file = _getfstream(cmd.cmdInfoType);

	file << res;
}

std::ostream &Logger::_getfstream(plazza::Information type)
{
	switch (type) {
	case PHONE_NUMBER:
		return _phoneFile;
	case EMAIL_ADDRESS:
		return _emailFile;
	case IP_ADDRESS:
		return _ipFile;
	default:
		return _unsorted;
	}
	return _unsorted;
}
