#pragma once

#include <string>

#include "ILogger.h"

namespace alxutils {

class ConsoleLogger : public ILogger {
public:
	virtual void logEntry(const ELogEntryType & entryType, const std::string & str) override;
};

}


