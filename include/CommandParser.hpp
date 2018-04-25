/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** CommandParser
*/

#ifndef COMMANDPARSER_HPP_
	#define COMMANDPARSER_HPP_

	#include <unordered_map>
	#include <queue>
	#include "Command.hpp"

namespace plazza {
	class CommandParser;
	class CommandParserError;
	constexpr auto ERR_CMD_TYPE (
		":\033[1;31m error:\033[0m Please specify \
the \033[1minformation type\033[m to get");
	constexpr auto ERR_FILE_NAME (
		":\033[1;31m error:\033[0m Please check \
the \033[1mfilename\033[m");
}

class plazza::CommandParser {
public:
	using InfoTypeMap =
		std::unordered_map<std::string, enum Information>;
	CommandParser(std::queue<plazza::Command> &cmdqueue)
		: _cmdqueue(cmdqueue), _cmdId(0)
		{}
	~CommandParser() {}
	void ParseLine(std::string &line);
	void dump() noexcept;
private:
	void ParseInstruction(std::string &instruction);
	void _ChangeToUpperCase(std::string &_line);
	void _CreateCommand(std::string &cmdFileName,
				const std::string &);
	void _CleanStringSpace(std::string &_line);
	void _SetCommandType(std::string &_line);
	void _extractAllFileName(std::string &_line);
	void _extractInstruction(std::string &line);
	static bool _CleanSpacers(char a, char b);
	enum Information _getInfoType(std::string _stringInfo);
	bool _checkFileAccess(std::string &filename);

	std::queue<std::string> _instructionqueue;
	std::queue<plazza::Command> &_cmdqueue;
	int _cmdId;
	std::string _cmdType;
};

class plazza::CommandParserError : std::exception {
public:
	CommandParserError(std::string prefix, int err);
	CommandParserError(std::string prefix);
	const char *what() const noexcept;
public:
	std::string _what;
};

#endif /* !COMMANDPARSER_HPP_ */
