#include "WorkerThread.h"

namespace threadpool {

WorkerThread::WorkerThread() {
	m_id = reinterpret_cast<WorkerID>(this);
	m_thread = std::thread(&WorkerThread::threadLoop, this);
}

WorkerThread::~WorkerThread() {
	dbgtrace;
	if (m_thread.joinable())
		m_thread.join();
}

void WorkerThread::doTask(TaskCtx && taskCtx) {
	dbgtrace;
	sendMsg(make_unique<NewTaskMsg>(std::move(taskCtx)));
}

void WorkerThread::stop() {
	dbgtrace;
	sendMsg(make_unique<StopMsg>());
	m_thread.join();
}

void WorkerThread::threadLoop() {
	dbgtrace;
	while (true) {
		std::unique_ptr<IWorkerThreadMsg> msg(std::move(recvMsg()));
		if (instance_of<NewTaskMsg>(*msg)) {
			dbglog("got new task msg");
			std::unique_ptr<NewTaskMsg> taskMsg(dynamic_unique_cast<NewTaskMsg>(msg));
			TaskCtx & taskCtx = taskMsg->taskCtx;

			taskCtx.executor(std::move(taskCtx.task));
			taskCtx.onTaskDone();
		}
		else if (instance_of<StopMsg>(*msg)) {
			dbglog("got stop msg");
			return;
		}
	}
}

}

namespace std {
	std::hash<WorkerThread::WorkerID> hash<std::shared_ptr<WorkerThread>>::s_hashWorkerID;
}
