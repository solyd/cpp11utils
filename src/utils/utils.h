#pragma once

#include <memory>
#include <utility>
#include <sstream>
#include <iostream>
#include <mutex>
#include <string>

namespace alxutils {

#define _CONCAT_(x, y) x##y
#define CONCAT(x, y) _CONCAT_(x, y)

#define DO_TIMES_WITH_VAR(ntimes, varname) \
	for (uint varnam	e = 0; varname < ntimes; ++varname)

#define DO_TIMES(ntimes) \
	DO_TIMES_WITH_VAR(ntimes, CONCAT(_anonymousvar, __LINE__))

template<typename TTo, typename TFrom>
std::unique_ptr<TTo> dynamic_unique_cast(std::unique_ptr<TFrom> & from) {
	if (!from)
		return std::unique_ptr<TTo>();

	std::unique_ptr<TTo> to(dynamic_cast<TTo *>(from.get()));
	from.release();

	return std::move(to);
}

// returns true if a is instance of type B
template<typename B, typename A>
bool instance_of(const A & a) {
	return dynamic_cast<B const*>(&a) != nullptr;
}

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// use operator<< for default printing
template<typename T>
inline std::string to_string(const T & arg) {
	std::stringstream strm;
	strm << arg;
	return strm.str();
}

template<typename T, typename... Ts>
inline std::string to_string(const T & head, const Ts &... tail) {
	return to_string(head).append(to_string(tail...));
}

extern std::mutex g_printlnLock;

template<typename... Ts>
inline void println(const Ts &... args) {
	std::lock_guard<std::mutex> lock(g_printlnLock);
	std::cout << to_string(args...) << std::endl;
}

} // namespace alxutils



