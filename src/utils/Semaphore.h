#pragma once

#include <condition_variable>
#include <mutex>

#include "src/utils/types.h"
#include "src/utils/Range.h"

namespace alxutils {

class Semaphore {
public:
	Semaphore(const int val, const Range<int> range);

	bool tryWait();
	void wait();
	void notifyOne();
	void notifyAll();

private:
	int inc_val();
	int dec_val();

private:
	int 										m_val;
	Range<int>							m_range;
	std::condition_variable m_cond;
	std::mutex							m_lock;
};

class EventFlag : public Semaphore {
public:
	EventFlag();
};

}
