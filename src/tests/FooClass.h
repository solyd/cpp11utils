#pragma once

#include <utility>
#include <vector>

#include "src/utils/utils.h"

namespace tests {

using namespace alxutils;

template<typename T>
class DbgContainer {
public:
	DbgContainer() { dbgtrace; }
	DbgContainer(const T & t) : m_t(t) { dbgtrace; }
	DbgContainer(const DbgContainer & other) : m_t(other.m_t) { dbgtrace; }
	DbgContainer(DbgContainer && other) : m_t(std::move(other.m_t)) { dbgtrace; }

	DbgContainer& operator=(const DbgContainer & other) {
		dbgtrace;
		m_t = other.m_t;
		return *this;
	}

	DbgContainer& operator=(DbgContainer && other) {
		dbgtrace;
		m_t = std::move(other.m_t);
		return *this;
	}

	~DbgContainer() {
		dbgtrace;
	}

	T m_t;
};

class FooClass {
public:
	FooClass(int x, int y) : m_x(x), m_y(y) {
		dbgtrace;
		fillData();
	}

	FooClass() : m_x(0), m_y(0) {
		dbgtrace;
		fillData();
	}

	FooClass(const FooClass & other) {
		dbgtrace;
		copyFrom(other);
	}

	FooClass(FooClass && other) {
		dbgtrace;
		copyFrom(std::move(other));
	}

	FooClass& operator=(const FooClass & other) {
		dbgtrace;
		copyFrom(other);
		return *this;
	}

	FooClass& operator=(FooClass && other) {
		dbgtrace;
		copyFrom(std::move(other));
		return *this;
	}

	~FooClass() {
		dbgtrace;
	}

	void copyFrom(const FooClass & other) {
		m_x = other.m_x;
		m_y = other.m_y;
		m_data = other.m_data;
	}

	void copyFrom(FooClass && other) {
		m_x = std::move(other.m_x);
		m_y = std::move(other.m_y);
		m_data = std::move(other.m_data);
	}

	void fillData() {
//		m_data.resize(5);
//		DO_TIMES(3) {
//			m_data.emplace_back(3);
//		}
	}

	int m_x;
	int m_y;
	std::vector<DbgContainer<int>> m_data;
};

}
