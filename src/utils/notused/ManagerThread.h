#pragma once

#include <thread>
#include <list>
#include <memory>

//#include "ThreadPool.h"
#include "WorkerThread.h"

#include "src/utils/utils.h"
#include "src/utils/MessageReceiver.h"

namespace alxutils {

using threadsafe::Queue;
using threadsafe::HashSet;

struct IManagerThreadMsg : public AbstractBase {};

class ManagerThread : public MessageReceiver<std::unique_ptr<IManagerThreadMsg>> {
public:
	struct NewTaskMsg : public IManagerThreadMsg {
		NewTaskMsg(ThreadPool::Task && task_) : task(std::move(task_)) {}
		ThreadPool::Task task;
	};
	struct StopMsg : public IManagerThreadMsg {};

	ManagerThread();
	~ManagerThread();

private:
	void threadLoop();

private:
	std::thread m_thread;
	std::list<std::shared_ptr<WorkerThread>> m_workers;
	Queue<std::shared_ptr<WorkerThread>> m_availableWorkers;
	HashSet<std::shared_ptr<WorkerThread>> m_busyWorkers;
};

}




