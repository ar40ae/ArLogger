#include "arlogger/DefaultFormatter.h"
#include "arlogger/LogLevel.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <utility>

namespace arlogger
{
    DefaultFormatter::DefaultFormatter(std::string pattern)
        : m_pattern(std::move(pattern))
    {
    }

    std::string DefaultFormatter::format(const LogRecord& record) const
    {
        const auto time =
            std::chrono::system_clock::to_time_t(record.timestamp);

        std::tm localTime{};

        localtime_s(&localTime, &time);

        std::ostringstream timeStream;
        timeStream << std::put_time(&localTime, "%H:%M:%S");

        std::ostringstream dateStream;
        dateStream << std::put_time(&localTime, "%Y/%m/%d");

        std::string result = m_pattern;

        auto replace = [&](const std::string& key, const std::string& value)
            {
                std::size_t position = 0;

                while ((position = result.find(key, position)) != std::string::npos)
                {
                    result.replace(position, key.length(), value);
                    position += value.length();
                }
            };

        replace("%time", timeStream.str());
        replace("%date", dateStream.str());
        replace("%level", toString(record.level));
        replace("%logger", record.loggerName);
        replace("%message", record.message);
        replace("%file", record.location.file_name());
        replace("%line", std::to_string(record.location.line()));
        replace("%function", record.location.function_name());

        return result;
    }
}