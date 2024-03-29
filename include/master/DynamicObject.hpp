/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** DynamicObject
*/

#ifndef DYNAMICOBJECT_HPP_
	#define DYNAMICOBJECT_HPP_

#include <dlfcn.h>

namespace plazza::master {
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
		T *get(char **arg) noexcept
		{
			return call(arg);
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
		T	*(*call)(char **);
		void	*_handle;

		void _init(const std::string &dl, const std::string &sym)
		{
			if (dl.length() == 0)
				throw std::runtime_error("No lib available");
			_handle = dlopen(dl.c_str(), RTLD_LAZY);
			std::cout << dlerror() << std::endl;
			if (!_handle)
				throw std::runtime_error(dlerror());
			dlerror();
			call = (T *(*)(char **)) dlsym(_handle, sym.c_str());
			const char *dlsym_error(dlerror());
			if (dlsym_error)
				throw std::runtime_error(dlsym_error);
		}
	};
}

#endif /* !DYNAMICOBJECT_HPP_ */
