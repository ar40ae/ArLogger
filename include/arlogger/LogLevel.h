#pragma once

#include <string>

namespace arlogger {
	enum class LogLevel {
		Trace,
		Debug,
		Info,
		Warning,
		Error,
		Critical
	};

	std::string toString(LogLevel level);

	int toValue(LogLevel level);
}