#pragma once

#include <memory>
#include <utility>
#include <sstream>
#include <iostream>
#include <mutex>
#include <string>

#include "src/utils/types.h"
#include "src/utils/logger/ILogger.h"

namespace alxutils {

#define _CONCAT_(x, y) x##y
#define CONCAT(x, y) _CONCAT_(x, y)

#define DO_TIMES_WITH_VAR(ntimes, varname) \
	for (uint varname = 0; varname < ntimes; ++varname)

#define DO_TIMES(ntimes) \
	DO_TIMES_WITH_VAR(ntimes, CONCAT(_anonymousvar, __LINE__))

#ifdef ENABLE_DEBUG_MODE
#define dbgtrace alxutils::log_dbg("called\t", __PRETTY_FUNCTION__)
#define dbglog(...) alxutils::log_dbg("[", __PRETTY_FUNCTION__, "] ", __VA_ARGS__)
#else
#define dbgtrace
#define dbglog(...)
#endif

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

template<typename... Ts>
inline void log_dbg(const Ts &... args) {
	getLogger()->logEntry(ELogEntryType::DEBUG, to_string(args...));
}

template<typename... Ts>
inline void log_info(const Ts &... args) {
	getLogger()->logEntry(ELogEntryType::INFO, to_string(args...));
}

template<typename... Ts>
inline void log_error(const Ts &... args) {
	getLogger()->logEntry(ELogEntryType::ERROR, to_string(args...));
}

extern std::mutex g_printlnLock;

template<typename... Ts>
inline void println(const Ts &... args) {
	std::lock_guard<std::mutex> lock(g_printlnLock);
	std::cout << to_string(args...) << std::endl;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template<bool enable, typename Ttrue = void, typename Tfalse = void>
struct enable_if_else {};

template<typename Ttrue, typename Tfalse>
struct enable_if_else<true, Ttrue, Tfalse> {
	typedef Ttrue type;
};

template<typename Ttrue, typename Tfalse>
struct enable_if_else<false, Ttrue, Tfalse> {
	typedef Tfalse type;
};

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

struct AbstractBase { virtual ~AbstractBase() = 0; };


} // namespace alxutils


























