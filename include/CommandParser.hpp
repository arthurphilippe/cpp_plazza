/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** CommandParser
*/

#ifndef COMMANDPARSER_HPP_
	#define COMMANDPARSER_HPP_

	#include <unordered_map>
	#include <queue>
	#include "Command.hpp"

namespace Plazza {
	class CommandParser;
};

class Plazza::CommandParser {
	public:
		using InfoTypeMap =
			std::unordered_map<std::string, enum Information>;
		CommandParser(std::queue<Plazza::Command> &cmdqueue)
			: _cmdqueue(cmdqueue), _cmdId(0)
			{}
		~CommandParser() {}
		void ParseLine(std::string &line);
	private:
		void _ChangeToUpperCase(std::string &_line);
		void _CreateCommand(std::string &cmdFileName,
					const std::string &) noexcept;
		void _CleanStringSpace(std::string &_line);
		void _SetCommandType(std::string &_line);
		void _extractAllFileName(std::string &_line);
		static bool _CleanSpacers(char a, char b);
		enum Information _getInfoType(std::string _stringInfo);



		std::queue<Plazza::Command> _cmdqueue;
		int _cmdId;
		std::string _cmdType;
};

#endif /* !COMMANDPARSER_HPP_ */
