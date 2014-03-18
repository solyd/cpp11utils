#include "tests.h"

#include <random>
#include <cassert>
#include <chrono>
#include <list>
#include <future>

#include "src/utils/utils.h"
#include "src/utils/threadpool/ThreadPool.h"
#include "src/utils/collections/Queue.h"
#include "src/utils/collections/threadsafe/Queue.h"
#include "src/utils/logger/ILogger.h"

namespace tests {
using alxutils::log_info;
using alxutils::println;

std::random_device rd;
std::uniform_int_distribution<uint> dist(100, 2500);

uint get_random(uint min, uint max) {
	return std::uniform_int_distribution<uint>(min, max)(rd);
}

void thread_sleep_random() {
	std::this_thread::sleep_for(std::chrono::milliseconds(dist(rd)));
}

void test_all() {
	test_ThreadPool();
	test_threadsafe_Queue();
}


void test_threadsafe_Queue() {
	log_info("testing threadsafe queue");
	using threadsafe::Queue;


}

void test_ThreadPool() {
	log_info("testing thread pool");
	using threadpool::ThreadPool;

	ThreadPool pool;

	std::list<std::future<void>> results;
	log_info("doing first batch of jobs");
	int  jobNum = 0;
	DO_TIMES(20) {
		std::function<void()> f = [jobNum] () {
			println("job #", jobNum, " before sleep");
			thread_sleep_random();
			println("job #", jobNum, " after sleep");
		};
		++jobNum;

		results.push_back(pool.run(f));
	}

	log_info("going to sleep for 5 seconds");
	std::this_thread::sleep_for(std::chrono::seconds(5));

	log_info("doing second batch of jobs");
	DO_TIMES(20) {
		std::function<void()> f = [jobNum] () {
			println("job #", jobNum, " before sleep");
			thread_sleep_random();
			println("job #", jobNum, " after sleep");
		};
		++jobNum;

		results.push_back(pool.run(f));
	}

	for (auto & res : results)
		res.wait();
}


}
