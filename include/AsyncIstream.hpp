/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** AsyncIstream
*/

#ifndef ASYNCISTREAM_HPP_
	#define ASYNCISTREAM_HPP_

#include <iostream>
#include <chrono>
#include <thread>
#include <queue>
#include <string>
#include <atomic>
#include <mutex>

namespace plazza {
	class AsyncIstream;
}

class plazza::AsyncIstream {
public:
	AsyncIstream(std::istream &stream = std::cin);
	bool isReady();
	std::string getLine();
	inline bool stillRunning()
	{
		return !_eof || isReady();
	}

private:
	std::istream &_stream;
	std::atomic_bool _eof;
	std::mutex _mutex;
	std::queue<std::string> _queue;
	std::thread _thread;

	void _threadEntry();
};

// int main() {
// 	AsyncIstream reader{&std::cin};

// 	while (true) {
// 		while (reader.isReady()) {
// 			std::cout << "input received: " << reader.getLine() << std::endl;
// 		}
// 		if (reader.stillRunning()) {
// 			std::cout << "still waiting..." << std::endl;
// 		} else {
// 			std::cout << "eof" << std::endl;
// 		}
// 		std::this_thread::sleep_for(std::chrono::seconds(1));
// 	}
// }

#endif /* !ASYNCISTREAM_HPP_ */
