#pragma once

#include "Logger.h"

#include <memory>
#include <string>
#include <vector>

namespace arlogger
{
    class LoggerBuilder
    {
    public:
        LoggerBuilder& setLevel(LogLevel level);

        LoggerBuilder& setFlushLevel(LogLevel level);

        LoggerBuilder& setParent(
            std::shared_ptr<Logger> parent
        );

        LoggerBuilder& addSink(
            std::shared_ptr<Sink> sink
        );

        std::shared_ptr<Logger> build(
            const std::string& name
        ) const;

    private:
        LogLevel m_level = LogLevel::Info;
        LogLevel m_flushLevel = LogLevel::Error;

        std::shared_ptr<Logger> m_parent;

        std::vector<std::shared_ptr<Sink>> m_sinks;
    };
}