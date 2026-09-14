#pragma once

#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <chrono>
#include <source_location>
#include "LogLevel.h"
#include "Sink.h"

namespace arlogger
{
    class Logger
    {
    public:
        explicit Logger(std::string name);

        void addSink(std::shared_ptr<Sink> sink);

        void trace(const std::string& message, const std::source_location& location = std::source_location::current());
        void debug(const std::string& message, const std::source_location& location = std::source_location::current());
        void info(const std::string& message, const std::source_location& location = std::source_location::current());
        void warning(const std::string& message, const std::source_location& location = std::source_location::current());
        void error(const std::string& message, const std::source_location& location = std::source_location::current());
        void critical(const std::string& message, const std::source_location& location = std::source_location::current());

        void setLevel(LogLevel level);
        LogLevel getLevel() const;

    private:
        void log(LogLevel level, const std::string& message, const std::source_location& location);

        std::string m_name;
        std::vector<std::shared_ptr<Sink>> m_sinks;
        LogLevel m_level;
    };
}