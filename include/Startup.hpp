/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Startup
*/

#ifndef STARTUP_HPP_
	#define STARTUP_HPP_

namespace plazza {
	class Startup;
	constexpr auto INVALID_ARGS(": arguments are invalid.");
	constexpr auto EXT_ERR(84);
	constexpr auto EXT_OK(0);
}

class plazza::Startup {
public:
	Startup(int argc, char **argv);
	~Startup();
	int launch();
private:
	int ac;
	char **av;

	void _startMaster();
	void _startChild();
};

#endif /* !STARTUP_HPP_ */
