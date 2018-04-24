/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** CommandParser
*/

#include <iostream>
#include <algorithm>
#include "CommandParser.hpp"
#include "Information.hpp"

static const Plazza::CommandParser::InfoTypeMap _infoTypeMap = {
	{"PHONE_NUMBER", Plazza::Information::PHONE_NUMBER},
	{"EMAIL_ADDRESS", Plazza::Information::EMAIL_ADDRESS},
	{"IP_ADDRESS", Plazza::Information::IP_ADDRESS},
	{"NONE", Plazza::Information::NONE},
};

bool Plazza::CommandParser::_CleanSpacers(char a, char b)
{
	if (a == b && a == ' ')
		return true;
	return false;
}

void Plazza::CommandParser::_CleanStringSpace(std::string &_line)
{
	std::string::iterator it;

	it = std::unique(_line.begin(), _line.end(), _CleanSpacers);
	_line.erase(it, _line.end());
	if (_line[0] == ' ')
		_line = _line.substr(1, _line.length());
	if (_line.length() > 0) {
		if (_line[_line.length() - 1] == ' ')
		_line = _line.substr(0, _line.length() - 1);
	}
}

void Plazza::CommandParser::_CreateCommand(
					std::string &cmdFileName,
					const std::string &infoType) noexcept
{
	Plazza::Command cmd;

	cmd.cmdFileName = cmdFileName;
	cmd.cmdId = _cmdId++;
	cmd.cmdInfoType = _getInfoType(infoType);
	_cmdqueue.push(cmd);
}

void Plazza::CommandParser::_ChangeToUpperCase(std::string &_line)
{
	std::transform(_line.begin(), _line.end(),_line.begin(), toupper);
}

enum Plazza::Information Plazza::CommandParser::_getInfoType(
						std::string _stringInfo)
{
	for (auto i = _infoTypeMap.begin(); i != _infoTypeMap.end(); i++) {
		if (i->first == _stringInfo)
			return i->second;
	}
	return Information::NONE;
}

void Plazza::CommandParser::_SetCommandType(std::string &_line)
{
	size_t space_place = _line.find_last_of(' ', _line.length());

	if (space_place == std::string::npos)
		throw ("Kappa");
	_cmdType = _line.substr(space_place + 1, _line.length());
	_ChangeToUpperCase(_cmdType);
}

/*
**	PK JE DOIS METTRE UN IF POUR BREAK CETTE BOUCLE EXPLIQUE
*/
void Plazza::CommandParser::_extractAllFileName(std::string &_line)
{
	size_t z = 0;
	size_t i = 0;
	size_t last_space = _line.find_last_of(' ', _line.length());
	std::string tmp;
	std::string first_info = _line.substr(0, _line.find(' '));

	_CreateCommand(first_info, _cmdType);
	std::cout << "Actual string: " << _line << std::endl;
	while (z < last_space) {
		if ((i = _line.find(' ')) == std::string::npos)
			break;
		z += i + 1;
		if (z >= last_space)
			break;
		tmp = _line.substr(i + 1, _line.find(' '));
		_CreateCommand(tmp, _cmdType);
		_line = _line.substr(_line.find(' ') + 1);
	}
}

void Plazza::CommandParser::ParseLine(std::string &line)
{
	std::string _line = line;

	_CleanStringSpace(_line);
	_SetCommandType(_line);
	_extractAllFileName(_line);
	while (!_cmdqueue.empty()) {
		std::cout << "Nom du fichier: " << _cmdqueue.front().cmdFileName;
		std::cout << " | Type: " << _cmdqueue.front().cmdInfoType;
		std::cout << " | ID: " << _cmdqueue.front().cmdId << std::endl;
		_cmdqueue.pop();
	}
	_cmdType.clear();
}
