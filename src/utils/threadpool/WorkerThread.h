#pragma once

#include <memory>
#include <functional>
#include <mutex>
#include <thread>
#include <utility>

#include "IThreadPool.h"
#include "src/utils/utils.h"
#include "src/utils/MessageReceiver.h"

namespace threadpool {

using namespace alxutils;

struct IWorkerThreadMsg : AbstractBase {};

// WorkerThread is NOT synchronized, meaning it can be "managed" only by a single
// thread. So no sharing of worker threads across thread pools
class WorkerThread : private MessageReceiver<std::unique_ptr<IWorkerThreadMsg>> {
public:
	typedef uint64_t WorkerID;

	WorkerThread();
	~WorkerThread();
	inline WorkerID id() const { return m_id; }

	void doTask(TaskCtx && taskCtx);
	void stop();

private:
	struct StopMsg : IWorkerThreadMsg {};
	struct NewTaskMsg : IWorkerThreadMsg {
		NewTaskMsg(TaskCtx && taskCtx_) : taskCtx(std::move(taskCtx_)) {}
		TaskCtx taskCtx;
	};

	void threadLoop();

private:
	std::thread 				 m_thread;
	WorkerID						 m_id;
};

}

namespace std {
using threadpool::WorkerThread;

template<>
struct hash<std::shared_ptr<WorkerThread>> {
	static std::hash<WorkerThread::WorkerID> s_hashWorkerID;

	std::size_t operator()(const std::shared_ptr<const WorkerThread> & worker) const {
		return s_hashWorkerID(worker->id());
	}
};

template<>
struct equal_to<std::shared_ptr<WorkerThread>> {
	bool operator()(const std::shared_ptr<const WorkerThread> & w1,
	                const std::shared_ptr<const WorkerThread> & w2) const
	{
		return w1->id() == w2->id();
	}
};
}
