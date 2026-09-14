#pragma once

#include "Formatter.h"

namespace arlogger
{
    class DefaultFormatter : public Formatter
    {
    public:
        explicit DefaultFormatter(std::string pattern = "[%date  %time] [%level] [%logger] %message");

        std::string format(const LogRecord& record) const override;
    private:
        std::string m_pattern;
    };
}