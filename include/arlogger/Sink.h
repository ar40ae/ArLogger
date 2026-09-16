#pragma once

#include "LogRecord.h"
#include "Formatter.h"

namespace arlogger {
	class Sink {
	public:
		explicit Sink(std::shared_ptr<Formatter> formatter);
		virtual ~Sink() = default;

		virtual void write(const LogRecord& record) = 0;
		virtual void flush() = 0;
	protected:
		std::shared_ptr<Formatter> m_formatter;
	};
}