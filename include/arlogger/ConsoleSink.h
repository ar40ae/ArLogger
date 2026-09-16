#pragma once

#include "Sink.h"

namespace arlogger {
	class ConsoleSink : public Sink {
	public:
		explicit ConsoleSink(std::shared_ptr<Formatter> formatter);

		void write(const LogRecord& record) override;
		void flush() override;
	};
}