#include "arlogger/Logger.h"
#include "arlogger/LogRecord.h"

#include <iostream>


namespace arlogger {
    Logger::Logger(std::string name)
        : m_name(std::move(name)), m_level(LogLevel::Info)
	{
	}

    void Logger::setLevel(LogLevel level) {
        m_level = level;
    }
    
    LogLevel Logger::getLevel() const {
        return m_level;
    }

    void Logger::addSink(std::shared_ptr<Sink> sink) {
        m_sinks.push_back(std::move(sink));
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

    void Logger::log(LogLevel level, const std::string& message, const std::source_location& location)
    {
        if (toValue(level) < toValue(m_level))
            return;

        LogRecord record{
            level,
            m_name,
            message,
            std::chrono::system_clock::now(),
            location
        };

        for (const auto& sink : m_sinks)
        {
            sink->write(record);
        }
    }

}
