#include "arlogger/FileSink.h"

#include <utility>

namespace arlogger {
	FileSink::FileSink(const std::string& filePath, 
		std::shared_ptr<Formatter> formatter) : 
		Sink(std::move(formatter)),
		m_file(filePath, std::ios::app) 
	{
	}

	void FileSink::write(const LogRecord& record) {
		if (!m_file.is_open())
			return;
		m_file << m_formatter->format(record) << '\n';
		m_file.flush();
	}
}