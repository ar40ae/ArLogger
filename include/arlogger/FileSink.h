#pragma once

#include "Sink.h"

#include <fstream>
#include <string>

namespace arlogger {
	class FileSink : public Sink {
	public:
		FileSink(const std::string& filePath, std::shared_ptr<Formatter> formatter);

		void write(const LogRecord& record) override;
	private:
		std::ofstream m_file;
	};
}