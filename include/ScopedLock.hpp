/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ScopedLock
*/

#ifndef SCOPEDLOCK_HPP_
	#define SCOPEDLOCK_HPP_

	#include <mutex>

namespace Plazza {
	class ScopedLock;
}

class Plazza::ScopedLock {
public:
	ScopedLock(std::mutex &mutex)
		: _mutex(mutex)
	{
		lock();
	}
	~ScopedLock()
	{
		unlock();
	}
	void lock()
	{
		_mutex.lock();
	}
	void unlock()
	{
		_mutex.unlock();
	}
	void trylock()
	{
		_mutex.try_lock();
	}
private:
	std::mutex &_mutex;
};

#endif /* !SCOPEDLOCK_HPP_ */
