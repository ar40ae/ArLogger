#include "../include/arlogger/LoggerBuilder.h"

#include <algorithm>
#include <utility>

namespace arlogger
{
    LoggerBuilder& LoggerBuilder::setLevel(LogLevel level)
    {
        m_level = level;
        return *this;
    }

    LoggerBuilder& LoggerBuilder::setFlushLevel(LogLevel level)
    {
        m_flushLevel = level;
        return *this;
    }

    LoggerBuilder& LoggerBuilder::setParent(
        std::shared_ptr<Logger> parent
    )
    {
        m_parent = std::move(parent);
        return *this;
    }

    LoggerBuilder& LoggerBuilder::addSink(
        std::shared_ptr<Sink> sink
    )
    {
        if (!sink)
            return *this;

        if (std::find(
            m_sinks.begin(),
            m_sinks.end(),
            sink
        ) == m_sinks.end())
        {
            m_sinks.push_back(std::move(sink));
        }

        return *this;
    }

    std::shared_ptr<Logger> LoggerBuilder::build(
        const std::string& name
    ) const
    {
        auto logger = std::make_shared<Logger>(
            name,
            m_parent
        );

        logger->setLevel(m_level);
        logger->setFlushLevel(m_flushLevel);

        for (const auto& sink : m_sinks)
        {
            logger->addSink(sink);
        }

        return logger;
    }
}