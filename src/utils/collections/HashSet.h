#pragma once

#include <unordered_set>
#include <functional>
#include <utility>
#include <mutex>
#include <memory>

namespace threadsafe {

template<
	class Key,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>,
	class Allocator = std::allocator<Key>
>
class HashSet {
private:
	typedef std::unordered_set<Key, Hash, KeyEqual, Allocator> Set;

public:
	typedef typename Set::iterator iterator;
	typedef typename Set::const_iterator const_iterator;

	std::pair<iterator, bool> insert(const Key & item) {
		std::lock_guard<std::mutex> lock(m_setLock);
		return m_set.insert(item);
	}

	iterator erase(const_iterator pos) {
		std::lock_guard<std::mutex> lock(m_setLock);
		return m_set.erase(pos);
	}

	void foreach(const std::function<void(const Key & item)> & f) {
		std::lock_guard<std::mutex> lock(m_setLock);
		for (const Key & item : m_set)
			f(item);
	}

private:
	Set m_set;
	std::mutex m_setLock;
};

} // namespace ThreadSafe




