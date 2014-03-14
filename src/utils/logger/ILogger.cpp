#include "ILogger.h"

#include <mutex>

#include "src/utils/logger/ConsoleLogger.h"

namespace alxutils {

std::mutex g_loggerLock;
std::unique_ptr<ILogger> g_logger;

std::unique_ptr<ILogger>& getLogger() {
	if (g_logger)
		return g_logger;

	{
		std::lock_guard<std::mutex> lock(g_loggerLock);
		if (g_logger)
			return g_logger;

		g_logger = std::unique_ptr<ConsoleLogger>(new ConsoleLogger());
		return g_logger;
	}
}

}
