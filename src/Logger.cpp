#include "arlogger/Logger.h"
#include "arlogger/LogRecord.h"

#include <iostream>
#include <algorithm>

namespace arlogger {
	Logger::Logger(std::string name)
		: m_name(std::move(name)),
		m_level(LogLevel::Info),
		m_flushLevel(LogLevel::Error)
	{
	}

	Logger::Logger(std::string name, std::shared_ptr<Logger> parent)
		: m_name(std::move(name)), 
		m_level(LogLevel::Info),
		m_flushLevel(LogLevel::Error),
		m_parent(std::move(parent))
	{
	}

	void Logger::setParent(std::shared_ptr<Logger> parent)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_parent = std::move(parent);
	}

	std::shared_ptr<Logger> Logger::getParent() 
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		return m_parent;
	}

	void Logger::setFlushLevel(LogLevel level)
	{
		m_flushLevel = level;
	}

	LogLevel Logger::getFlushLevel() const
	{
		return m_flushLevel;
	}

	void Logger::setLevel(LogLevel level) {
		m_level = level;
	}

	LogLevel Logger::getLevel() const {
		return m_level;
	}

	bool Logger::addSink(std::shared_ptr<Sink> sink) {
		if (!sink) {
			return false;
		}

		std::lock_guard<std::mutex> lock(m_mutex);

		if (std::find(m_sinks.begin(), m_sinks.end(), sink) != m_sinks.end())
			return false;

		m_sinks.push_back(std::move(sink));

		return true;
	}

	bool Logger::removeSink(const std::shared_ptr<Sink>& sink)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		auto it = std::find(m_sinks.begin(), m_sinks.end(), sink);

		if (it == m_sinks.end())
			return false;

		m_sinks.erase(it);
		return true;
	}

	void Logger::clearSinks()
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_sinks.clear();
	}

	void Logger::trace(const std::string& message, const std::source_location& location)
	{
		log(LogLevel::Trace, message, location);
	}

	void Logger::debug(const std::string& message, const std::source_location& location)
	{
		log(LogLevel::Debug, message, location);
	}

	void Logger::info(const std::string& message, const std::source_location& location)
	{
		log(LogLevel::Info, message, location);
	}

	void Logger::warning(const std::string& message, const std::source_location& location)
	{
		log(LogLevel::Warning, message, location);
	}

	void Logger::error(const std::string& message, const std::source_location& location)
	{
		log(LogLevel::Error, message, location);
	}

	void Logger::critical(const std::string& message, const std::source_location& location)
	{
		log(LogLevel::Critical, message, location);
	}

	void Logger::log(const LogRecord& record)
	{
		std::shared_ptr<Logger> parent;

		{
			std::lock_guard<std::mutex> lock(m_mutex);

			if (toValue(record.level) < toValue(m_level))
				return;

			LogRecord currentRecord = record;
			currentRecord.loggerName = m_name;

			for (const auto& sink : m_sinks)
			{
				sink->write(currentRecord);
			}

			if (toValue(record.level) >= toValue(m_flushLevel))
			{
				for (const auto& sink : m_sinks)
				{
					sink->flush();
				}
			}

			parent = m_parent;
		}

		if (parent)
		{
			parent->log(record);
		}
	}

	void Logger::log(LogLevel level, const std::string& message, const std::source_location& location)
	{
		LogRecord record{
		level,
		m_name,
		m_name,
		message,
		std::chrono::system_clock::now(),
		location
		};

		log(record);
	}

	void Logger::flush()
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		for (const auto& sink : m_sinks)
		{
			sink->flush();
		}
	}

}
