#pragma once

#include "arlogger/Sink.h"

namespace arlogger
{
    Sink::Sink(std::shared_ptr<Formatter> formatter)
        : m_formatter(std::move(formatter))
    {
    }
}