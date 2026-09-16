#pragma once

#include <string>
#include <chrono>
#include <source_location>

#include "LogLevel.h"

namespace arlogger{
	struct LogRecord {
		LogLevel level;
		std::string loggerName;
		std::string originLogger;
		std::string message;
		std::chrono::system_clock::time_point timestamp;
		std::source_location location;
	};
}