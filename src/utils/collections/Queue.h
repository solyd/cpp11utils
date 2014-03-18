#pragma once

#include <deque>
#include <utility>

#include "src/utils/types.h"

namespace alxutils {

template<typename TItem>
class Queue {
public:
	static const uint MAX_ITEMS_DEFAULT = UINT_MAX;
	Queue(const uint maxItems = MAX_ITEMS_DEFAULT) : m_maxItems(maxItems) {}

	bool enqueue(const TItem & item);
	bool enqueue(TItem && item);
	bool dequeue(TItem & out_item);
	void clear();
	uint size();
	void foreach(const std::function<void(TItem & item)> & f);

private:
	std::deque<TItem> m_queue;
	uint m_maxItems;
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template<typename TItem>
inline bool Queue<TItem>::enqueue(const TItem& item) {
	if (m_queue.size() >= m_maxItems)
		return false;

	m_queue.push_back(std::forward(item));
	return true;
}

template<typename TItem>
inline bool Queue<TItem>::enqueue(TItem&& item) {
	if (m_queue.size() >= m_maxItems)
		return false;

	m_queue.push_back(std::move(item));
	return true;
}

template<typename TItem>
inline void Queue<TItem>::clear() {
	m_queue.clear();
}

template<typename TItem>
inline uint Queue<TItem>::size() {
	return m_queue.size();
}

template<typename TItem>
inline bool Queue<TItem>::dequeue(TItem& out_item) {
	if (m_queue.empty())
		return false;

	out_item = std::move(m_queue.front());
	m_queue.pop_front();
	return true;
}

template<typename TItem>
inline void Queue<TItem>::foreach(const std::function<void(TItem& item)>& f) {
	for (TItem & item : m_queue)
		f(item);
}


}

