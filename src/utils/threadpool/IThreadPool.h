#pragma once

#include "src/utils/types.h"

namespace threadpool {

const uint NTHREADS_DEFAULT_MAX = UINT_MAX;
const uint NTHREADS_DEFAULT = 5;

typedef std::function<void()> Task;
typedef std::function<void()> FOnTaskDone;
typedef std::function<void(Task && task)> FTaskExecutor;

struct TaskCtx {
	TaskCtx(Task && task_,
	        FOnTaskDone && onTaskDone_,
	        FTaskExecutor && executor_ = [] (Task && task) { task(); }) :
		task(std::move(task_)), onTaskDone(std::move(onTaskDone_)), executor(std::move(executor_)) {}

	Task task;
	FOnTaskDone onTaskDone;
	FTaskExecutor executor;
};

}


