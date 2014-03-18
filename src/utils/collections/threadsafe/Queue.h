#pragma once

#include <deque>
#include <condition_variable>
#include <mutex>
#include <cassert>
#include <memory>
#include <utility>
#include <functional>

#include "src/utils/types.h"

namespace threadsafe {

template<typename TItem>
class Queue {
public:
	static const uint MAX_ITEMS_DEFAULT = UINT_MAX;
	Queue(const uint maxItems = MAX_ITEMS_DEFAULT) : m_maxItems(maxItems) {}

	bool enqueue(const TItem & item);
	bool enqueue(TItem && item);
	TItem dequeue(); // blocking
	bool dequeue(TItem & out_item);
	void clear();
	uint size();
	void foreach(const std::function<void(TItem & item)> & f);

private:
	std::deque<TItem> 			m_queue;
	std::mutex							m_queueLock;
	std::condition_variable m_queueNotEmpty;
	uint										m_maxItems;
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template<typename TItem>
inline bool Queue<TItem>::enqueue(const TItem& item) {
	{
		std::unique_lock<std::mutex> lock(m_queueLock);
		if (m_queue.size() >= m_maxItems)
			return false;
		m_queue.push_back(item);
	}

	m_queueNotEmpty.notify_one();
	return true;
}

template<typename TItem>
inline bool Queue<TItem>::enqueue(TItem&& item) {
	{
		std::unique_lock<std::mutex> lock(m_queueLock);
		if (m_queue.size() >= m_maxItems)
			return false;
		m_queue.push_back(std::move(item));
	}

	m_queueNotEmpty.notify_one();
	return true;
}

template<typename TItem>
inline TItem Queue<TItem>::dequeue() {
	std::unique_lock<std::mutex> lock(m_queueLock);
	while (m_queue.size() == 0)
		m_queueNotEmpty.wait(lock);

	TItem res = std::move(m_queue.front());
	m_queue.pop_front();
	return std::move(res);
}

template<typename TItem>
inline bool Queue<TItem>::dequeue(TItem& out_item) {
	std::unique_lock<std::mutex> lock(m_queueLock);
	if (m_queue.size() == 0)
		return false;

	out_item = std::move(m_queue.front());
	m_queue.pop();
	return true;
}

template<typename TItem>
inline void Queue<TItem>::clear() {
	std::unique_lock<std::mutex> lock(m_queueLock);
	while (! m_queue.empty())
		m_queue.pop_front();
}

template<typename TItem>
inline uint Queue<TItem>::size() {
	std::unique_lock<std::mutex> lock(m_queueLock);
	return m_queue.size();
}

template<typename TItem>
inline void Queue<TItem>::foreach(const std::function<void(TItem& item)>& f) {
	std::unique_lock<std::mutex> lock(m_queueLock);
	for (TItem & item : m_queue)
		f(item);
}

} // namespace ThreadSafe


