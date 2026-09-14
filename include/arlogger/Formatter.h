#pragma once

#include <string>

#include "LogRecord.h"

namespace arlogger
{
    class Formatter
    {
    public:
        virtual ~Formatter() = default;

        virtual std::string format(const LogRecord& record) const = 0;
    };
}