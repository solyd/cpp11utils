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

}



