#pragma once

#include "Sink.h"

#include <fstream>
#include <string>

namespace arlogger {
	enum class FileSinkError {
		None,
		OpenFailed,
		WriteFailed,
		RotationFailed
	};

	class FileSink : public Sink {
	public:
		FileSink(const std::string& filePath, std::shared_ptr<Formatter> formatter, std::uintmax_t maxFileSize = 10 * 1024 * 1024);

		void write(const LogRecord& record) override;

		void flush() override;
		void close();
		
		bool isOpen() const;
		bool hasError() const;
		FileSinkError getError() const;
	private:
		void rotate();

		FileSinkError m_error = FileSinkError::None;
		std::string m_filePath;
		std::uintmax_t m_maxFileSize;
		std::ofstream m_file;
	};
}