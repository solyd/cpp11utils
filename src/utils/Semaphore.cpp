#include "Semaphore.h"

#include <cassert>

namespace alxutils {
Semaphore::Semaphore(const int val, const Range<int> range) :
	m_val(val), m_range(range)
{
	assert(m_range.in_range(val));
}

bool Semaphore::tryWait() {
	std::unique_lock<std::mutex> lock(m_lock);
	if (m_val == m_range.min())
		return false;
	dec_val();
	return true;
}

void Semaphore::wait() {
	std::unique_lock<std::mutex> lock(m_lock);
	if (dec_val() == m_range.min())
		m_cond.wait(lock);
}

void Semaphore::notifyOne() {
	std::unique_lock<std::mutex> lock(m_lock);
	inc_val();
	lock.unlock();
	m_cond.notify_one();
}

void Semaphore::notifyAll() {
	std::unique_lock<std::mutex> lock(m_lock);
	inc_val();
	lock.unlock();
	m_cond.notify_all();
}

int Semaphore::inc_val() {
	if (m_val < m_range.max())
		return ++m_val;
	return m_val;
}

int Semaphore::dec_val() {
	if (m_val > m_range.min())
		return --m_val;
	return m_val;
}

EventFlag::EventFlag() :
	Semaphore(0, Range<int>(0, 1))
{
}

}
