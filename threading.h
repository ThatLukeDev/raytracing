#ifndef threading_h
#define threading_h

#include <thread>
#include <vector>
#include <mutex>
#include <functional>

using namespace std;

class jobHandler {public:
	vector<thread> threads;
	vector<function<void()>> queue;
	mutex queueMut;
	int count = thread::hardware_concurrency();
	bool running = false;
	bool autoStop = true;
	void start() {
		running = true;
		for (int i = 0; i < count; i++) {
			threads.push_back(thread([&]() {
				while (running) {
					function<void()> job = [](){};
					queueMut.lock();
					if (queue.empty()) {
						if (autoStop) {
							running = false;
						}
					}
					else {
						job = queue.front();
						queue.erase(queue.begin());
					}
					queueMut.unlock();
					job();
				}
			}));
		}
		for (int i = 0; i < count; i++) {
			threads[i].join();
		}
	}
	void addJob(function<void()> job) {
		queue.push_back(job);
	}
	void stop() {
		running = false;
	}
};
#endif
