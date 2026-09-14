#include "arlogger/ConsoleSink.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace arlogger {
	ConsoleSink::ConsoleSink(std::shared_ptr<Formatter> formatter)
		: Sink(std::move(formatter))
	{
	}

	void ConsoleSink::write(const LogRecord& record) {

		std::cout << m_formatter->format(record) << "\n";
	}
}