#pragma once

#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <chrono>
#include <source_location>
#include "LogLevel.h"
#include "Sink.h"
#include <mutex>

namespace arlogger
{
    class Logger
    {
    public:
        explicit Logger(std::string name);
        explicit Logger(std::string name, std::shared_ptr<Logger> parent);

        void setParent(std::shared_ptr<Logger> parent);
        std::shared_ptr<Logger> getParent();

        bool addSink(std::shared_ptr<Sink> sink);
        bool removeSink(const std::shared_ptr<Sink>& sink);
        void clearSinks();

        void flush();

        void trace(const std::string& message, const std::source_location& location = std::source_location::current());
        void debug(const std::string& message, const std::source_location& location = std::source_location::current());
        void info(const std::string& message, const std::source_location& location = std::source_location::current());
        void warning(const std::string& message, const std::source_location& location = std::source_location::current());
        void error(const std::string& message, const std::source_location& location = std::source_location::current());
        void critical(const std::string& message, const std::source_location& location = std::source_location::current());

        void setLevel(LogLevel level);
        LogLevel getLevel() const;

        void setFlushLevel(LogLevel level);
        LogLevel getFlushLevel() const;

    private:
        void log(LogLevel level, const std::string& message, const std::source_location& location);
        void log(const LogRecord& record);
        std::shared_ptr<Logger> m_parent;
        std::string m_name;
        std::vector<std::shared_ptr<Sink>> m_sinks;
        LogLevel m_level;
        LogLevel m_flushLevel;

        std::mutex m_mutex;
    };
}