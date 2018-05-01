#include <thread>
#include <iostream>
#include <string>
#include <stdexcept>
#include <dlfcn.h>
#include <stdio.h>
#include "IUserController.hpp"

namespace plazza {
	template <class T>
	class DynamicObject {
	public:
		DynamicObject(const std::string &dl,
				const std::string &sym = "Construct")
		{
			_init(dl, sym);
		}
		~DynamicObject()
		{
			dlclose(_handle);
		}
		T *get() noexcept
		{
			return call();
		}
		T *reset(const std::string &dl,
				const std::string &sym = "Construct")
		{
			dlclose(_handle);
			_handle = nullptr;
			_init(dl, sym);
			return call();
		}
	private:
		T	*(*call)();
		void	*_handle;

		void _init(const std::string &dl, const std::string &sym)
		{
			if (dl.length() == 0)
				throw std::runtime_error("No lib available");
			_handle = dlopen(dl.c_str(), RTLD_LAZY);
			if (!_handle)
				throw std::runtime_error(dlerror());
			dlerror();
			call = (T *(*)()) dlsym(_handle, sym.c_str());
			const char *dlsym_error(dlerror());
			if (dlsym_error)
				throw std::runtime_error(dlsym_error);
		}
	};
}

void prout(int ac, char **av)
{
	std::queue<plazza::Command> cmd;
	std::string _name(av[1]);
	plazza::DynamicObject<plazza::master::IUserController> _test(_name);
	auto kek = _test.get();
	kek->poll(cmd);
	delete kek;
}

int main(int ac, char **av)
{
	std::thread a(prout, ac, av);
	std::cout << "k" << std::endl;
	a.join();
}

// int main(int ac, char **av)
// {
// 	QApplication *_app(new QApplication(ac, av));
// 	std::queue<plazza::Command> cmdQ;
// 	plazza::master::PlazzaGui a(ac, av);
// 	_app->exec();
// 	a.poll(cmdQ);
// 	while (!cmdQ.empty()) {
// 		std::cout << "FileName: " <<cmdQ.front().cmdFileName
// 			<< " | ID: " << cmdQ.front().cmdId << std::endl;
// 		cmdQ.pop();
// 	}
// }
