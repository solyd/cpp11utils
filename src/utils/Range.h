#pragma once

namespace alxutils {

template<typename T>
class Range {
public:
	Range(const T & min, const T & max) : m_min(min), m_max(max) {}
	inline T min() const { return m_min; }
	inline T max() const { return m_max; }
	inline bool in_range(const T & val) const { return val >= m_min && val <= m_max; }

private:
	T m_min;
	T m_max;
};

}


