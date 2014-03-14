#include "ConsoleLogger.h"

#include <thread>

#include "src/utils/utils.h"

namespace alxutils {

void ConsoleLogger::logEntry(const ELogEntryType& entryType, const std::string & str) {
	println("[TID ", std::this_thread::get_id(), "] ", str);
}

}

