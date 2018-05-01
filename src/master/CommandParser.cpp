/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** CommandParser
*/

#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "CommandParser.hpp"
#include "Information.hpp"

using plazza::master::CommandParser;
using plazza::master::CommandParserError;

static const CommandParser::InfoTypeMap _infoTypeMap = {
	{"PHONE_NUMBER", plazza::Information::PHONE_NUMBER},
	{"EMAIL_ADDRESS", plazza::Information::EMAIL_ADDRESS},
	{"IP_ADDRESS", plazza::Information::IP_ADDRESS},
	{"NONE", plazza::Information::NONE},
};

bool CommandParser::_CleanSpacers(char a, char b)
{
	if (a == b && a == ' ')
		return true;
	return false;
}

void CommandParser::_CleanStringSpace(std::string &_line)
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

bool CommandParser::_checkFileAccess(std::string &filename)
{
std::ifstream istm(filename);
return istm.good();
}

void CommandParser::_CreateCommand(std::string &cmdFileName,
					const std::string &infoType)
{
	Command cmd;

	if (!_checkFileAccess(cmdFileName))
	{
		std::cerr << "\033[1m" + cmdFileName + "\033[m"
		<< ERR_FILE_NAME << std::endl;
		return;
	}
	cmd.cmdFileName = cmdFileName;
	cmd.cmdId = _cmdId++;
	cmd.cmdInfoType = _getInfoType(infoType);
	_cmdqueue.push(cmd);
}

void CommandParser::_ChangeToUpperCase(std::string &_line)
{
	std::transform(_line.begin(), _line.end(),_line.begin(), toupper);
}

enum plazza::Information
CommandParser::_getInfoType(std::string _stringInfo)
{
	for (auto i = _infoTypeMap.begin(); i != _infoTypeMap.end(); i++) {
		if (i->first == _stringInfo)
			return i->second;
	}
	return Information::NONE;
}

void CommandParser::_SetCommandType(std::string &_line)
{
	size_t space_place = _line.find_last_of(' ', _line.length());

	if (space_place == std::string::npos)
		throw (CommandParserError(
			"\033[1m" + _line + "\033[m" + ERR_CMD_TYPE));
	_cmdType = _line.substr(space_place + 1, _line.length());
	_line = _line.substr(0, space_place);
	_ChangeToUpperCase(_cmdType);
	if (_getInfoType(_cmdType) == Information::NONE)
		throw (CommandParserError(
			"\033[1m" + _line + "\033[m" + ERR_CMD_TYPE));
}

void CommandParser::_extractAllFileName(std::string &_line)
{
	size_t i = 0;
	std::string tmp;

	while (i != std::string::npos) {
		i = _line.find(' ');
		tmp = _line.substr(0, i);
		_CreateCommand(tmp, _cmdType);
		_line = _line.substr(i + 1);
	}
}

void CommandParser::_extractInstruction(std::string &line)
{
	size_t i = 0;
	std::string tmp;
	std::string _line = line;

	while (i != std::string::npos) {
		i = _line.find(';');
		tmp = _line.substr(0, i);
		_CleanStringSpace(tmp);
		_instructionqueue.push(tmp);
		_line = _line.substr(i + 1);
	}
}

void CommandParser::ParseInstruction(std::string &instruction)
{
	try {
		_CleanStringSpace(instruction);
		_SetCommandType(instruction);
		_extractAllFileName(instruction);
	} catch (const CommandParserError &error) {
		error.what();
	}
	_cmdType.clear();
}

void CommandParser::ParseLine(std::string &line)
{
	_CleanStringSpace(line);
	_extractInstruction(line);
	while (!_instructionqueue.empty()) {
		ParseInstruction(_instructionqueue.front());
		_instructionqueue.pop();
	}
}

void CommandParser::dump() noexcept
{
	while (!_cmdqueue.empty()) {
		std::cout << "Nom du fichier: ";
		std::cout << _cmdqueue.front().cmdFileName;
		std::cout << " | Type: " << _cmdqueue.front().cmdInfoType;
		std::cout << " | ID: " << _cmdqueue.front().cmdId << std::endl;
		_cmdqueue.pop();
	}
}

CommandParserError::CommandParserError(std::string prefix, int err)
	: _what(prefix + std::strerror(err))
{}

CommandParserError::CommandParserError(std::string prefix)
	: _what(prefix)
{}

const char *CommandParserError::what() const noexcept
{
	std::cerr << _what << std::endl;
	return _what.c_str();
}
