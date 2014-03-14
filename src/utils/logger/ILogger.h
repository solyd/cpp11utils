#pragma once

#include <string>
#include <memory>

namespace alxutils {

enum class ELogEntryType {
	INFO,
	ERROR,
	DEBUG
};

inline std::string to_string(const ELogEntryType & entryType) {
	switch (entryType) {
		case ELogEntryType::INFO: return "INFO";
		case ELogEntryType::DEBUG: return "DEBUG";
		case ELogEntryType::ERROR: return "ERROR";
	}
	return "INVALID";
}

class ILogger {
public:
	virtual void logEntry(const ELogEntryType & entryType, const std::string & str) = 0;
	virtual ~ILogger() {}
};

extern std::unique_ptr<ILogger> g_logger;
std::unique_ptr<ILogger>& getLogger();

template<typename... Ts>
inline void log(const ELogEntryType & entryType, const Ts &... args) {
	getLogger()->logEntry(entryType, to_string(args...));
}

template<typename... Ts>
inline void log(const Ts &... args) {
	log(ELogEntryType::DEBUG, args...);
}

#ifdef ENABLE_LOGGING
#define dbg(...) log("[", __PRETTY_FUNCTION__, "] ", __VA_ARGS__)
#else
#define dbg(...)
#endif

}



