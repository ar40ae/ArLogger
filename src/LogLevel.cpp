#include "arlogger/LogLevel.h"

#include <string>

namespace arlogger {
	std::string toString(LogLevel level) {
		switch (level) {
		case LogLevel::Trace:
			return "TRACE";

		case LogLevel::Debug:
			return "DEBUG";

		case LogLevel::Info:
			return "INFO";

		case LogLevel::Warning:
			return "WARNING";

		case LogLevel::Error:
			return "ERROR";

		case LogLevel::Critical:
			return "CRITICAL";

		default:
			return "UNKNOWN";
		}
	}
	int toValue(LogLevel level){
		return static_cast<int>(level);
	}
}