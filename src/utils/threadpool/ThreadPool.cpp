#include "ThreadPool.h"

#include <memory>
#include <thread>

namespace threadpool {

ThreadPool::ThreadPool(const uint minThreadCount, const uint maxThreadCount) :
	m_threadCount(minThreadCount, maxThreadCount),
	m_availableWorkers(std::make_shared<WorkerQ>())
{
	DO_TIMES(m_threadCount.min()) {
		auto worker = std::make_shared<WorkerThread>();
		m_workers.insert(worker);
		m_availableWorkers->enqueue(worker);
	}

	m_manager = std::thread(&ThreadPool::managerLoop, this);
}

ThreadPool::~ThreadPool() {
	dbgtrace;
	sendMsg(EThreadPoolMsg::STOP_WORKERS);
	m_manager.join();
}

std::future<void> ThreadPool::run(const std::function<void()> & f) {
	dbgtrace;
	auto asyncResult = std::make_shared<std::promise<void>>();

	enqueueTask([asyncResult, f] () {
		f();
		asyncResult->set_value();
	});

	return asyncResult->get_future();
}

void ThreadPool::enqueueTask(Task && task) {
	dbgtrace;
	m_tasks.enqueue(std::move(task));
	sendMsg(EThreadPoolMsg::NEW_TASK);
}

void ThreadPool::managerLoop() {
	dbgtrace;
	while (true) {
		auto msg = recvMsg();

		switch (msg) {
			case EThreadPoolMsg::NEW_TASK:
			{
				dbglog("got new task msg");
				auto task = m_tasks.dequeue();
				auto worker = m_availableWorkers->dequeue();
				auto & availableWorkers = m_availableWorkers;

				worker->doTask(TaskCtx(
						std::move(task),
						[worker, availableWorkers] () {
							availableWorkers->enqueue(worker);
						}
				));
			}
			break;

			case EThreadPoolMsg::STOP_WORKERS:
			{
				dbglog("got stop workers msg");
				m_workers.foreach([] (const std::shared_ptr<WorkerThread> & worker) {
					worker->stop();
				});
				return;
			}
			break;
		}
	}
}

}

