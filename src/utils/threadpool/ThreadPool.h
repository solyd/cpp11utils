#pragma once

#include <future>
#include <memory>
#include <utility>

#include "IThreadPool.h"
#include "WorkerThread.h"

#include "src/utils/Range.h"
#include "src/utils/collections/threadsafe/Queue.h"
#include "src/utils/collections/threadsafe/HashSet.h"
#include "src/utils/MessageReceiver.h"

namespace threadpool {

enum class EThreadPoolMsg {
	NEW_TASK,
	STOP_WORKERS
};

class ThreadPool : private MessageReceiver<EThreadPoolMsg> {
public:
	ThreadPool(const uint minThreadCount, const uint maxThreadCount);
	ThreadPool(const uint threadCount) : ThreadPool(threadCount, threadCount) {}
	ThreadPool() : ThreadPool(NTHREADS_DEFAULT, NTHREADS_DEFAULT) {}
	~ThreadPool();

	std::future<void> run(const std::function<void()> & f);

	template<typename Res>
	std::future<Res> run(const std::function<Res()> & f);

private:
	void enqueueTask(Task && task);
	void managerLoop();

private:
	typedef threadsafe::Queue<Task> TaskQ;
	typedef threadsafe::HashSet<std::shared_ptr<WorkerThread>> WorkerSet;
	typedef threadsafe::Queue<std::shared_ptr<WorkerThread>> WorkerQ;

	Range<uint> 						 m_threadCount;
	TaskQ 									 m_tasks;
	WorkerSet 							 m_workers;
	std::shared_ptr<WorkerQ> m_availableWorkers;
	std::thread 						 m_manager;
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template<typename Res>
std::future<Res> ThreadPool::run(const std::function<Res()> & f) {
	auto asyncResult = std::make_shared<std::promise<Res>>();
	enqueueTask([asyncResult, f] () {
		asyncResult->set_value(f());
	});
	return asyncResult->get_future();
}


}

