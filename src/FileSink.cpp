#include "arlogger/FileSink.h"

#include <utility>
#include <filesystem>

namespace arlogger {
	FileSink::FileSink(const std::string& filePath,
		std::shared_ptr<Formatter> formatter,
		std::uintmax_t maxFileSize) :
		Sink(std::move(formatter)),
		m_filePath(filePath),
		m_file(filePath, std::ios::app),
		m_maxFileSize(maxFileSize)
	{
		if (!m_file.is_open()) {
			m_error = FileSinkError::OpenFailed;
		}
	}

	void FileSink::write(const LogRecord& record) {
		if (!m_file.is_open())
		{
			return;
		}
		const std::string message =
			m_formatter->format(record) + '\n';

		std::error_code error;

		const auto currentSize =
			std::filesystem::file_size(m_filePath, error);

		if (!error && currentSize + message.size() > m_maxFileSize) {
			rotate();
		}

		if (!m_file.is_open()) {
			return;
		}

		m_file << message;

		if (m_file.fail()) {
			m_error = FileSinkError::WriteFailed;
		}
	}

	void FileSink::flush()
	{
		if (!m_file.is_open())
			return;

		m_file.flush();

		if (m_file.fail())
		{
			m_error = FileSinkError::WriteFailed;
		}
	}

	void FileSink::close()
	{
		if (!m_file.is_open())
			return;

		m_file.flush();

		if (m_file.fail())
		{
			m_error = FileSinkError::WriteFailed;
		}

		m_file.close();
	}

	bool FileSink::isOpen() const {
		return m_file.is_open();
	}

	FileSinkError FileSink::getError() const {
		return m_error;
	}

	bool FileSink::hasError() const {
		return m_error != FileSinkError::None;
	}

	void FileSink::rotate() {
		m_file.close();

		std::filesystem::path originalPath = m_filePath;

		std::uintmax_t index = 1;
		std::filesystem::path rotatedPath;

		do
		{
			rotatedPath = m_filePath + "." + std::to_string(index);
			++index;
		} while (std::filesystem::exists(rotatedPath));

		std::error_code error;

		std::filesystem::rename(
			originalPath,
			rotatedPath,
			error
		);

		if (error) {
			m_error = FileSinkError::RotationFailed;
			return;
		}

		m_file.open(m_filePath, std::ios::app);

		if (!m_file.is_open()) {
			m_error = FileSinkError::OpenFailed;
		}
	}

}