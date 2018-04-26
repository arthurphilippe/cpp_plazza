/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** AsyncIstream
*/

#include "AsyncIstream.hpp"

using plazza::AsyncIstream;

AsyncIstream::AsyncIstream(std::istream &stream)
	: _stream(stream), _eof(false),
	_thread([&] { _threadEntry(); })
{}

bool AsyncIstream::isReady()
{
	std::lock_guard<std::mutex> lk(_mutex);
	return !_queue.empty();
}

std::string AsyncIstream::getLine()
{
	std::lock_guard<std::mutex> lk(_mutex);
	if (_queue.empty()) {
		return {};
	}
	auto line = std::move(_queue.front());
	_queue.pop();
	return line;
}

void AsyncIstream::_threadEntry() {
	std::string line;

	while (std::getline(_stream, line)) {
		std::lock_guard<std::mutex> lk(_mutex);
		_queue.push(std::move(line));
	}
	_eof = true;
}
