# ArLogger

A lightweight and extensible C++ logging library for Windows.

ArLogger provides hierarchical loggers, customizable formatting, console and file sinks, log levels, source location tracking, thread safety, and automatic log file rotation.

## Features

* Windows support
* C++20
* Trace, Debug, Info, Warning, Error, and Critical log levels
* Hierarchical parent-child loggers
* Console sink
* File sink
* Customizable log formatting
* Source location tracking with `std::source_location`
* Thread-safe logging
* Log level filtering
* Configurable automatic flushing
* Log file size limits
* Non-destructive log rotation
* `LoggerBuilder` for convenient logger configuration

## Requirements

* Windows
* Visual Studio 2022
* C++20 or newer

## Basic Usage

```cpp
#include "arlogger/Logger.h"
#include "arlogger/ConsoleSink.h"
#include "arlogger/DefaultFormatter.h"

#include <memory>

int main()
{
    auto formatter =
        std::make_shared<arlogger::DefaultFormatter>();

    auto consoleSink =
        std::make_shared<arlogger::ConsoleSink>(formatter);

    arlogger::Logger logger("Engine");

    logger.addSink(consoleSink);

    logger.info("Engine started");
    logger.warning("Low texture memory");
    logger.error("Failed to load texture");
}
```

## LoggerBuilder

`LoggerBuilder` can be used to configure and create a logger using a fluent API.

```cpp
#include "arlogger/LoggerBuilder.h"

arlogger::LoggerBuilder builder;

auto logger = builder
    .setLevel(arlogger::LogLevel::Debug)
    .setFlushLevel(arlogger::LogLevel::Error)
    .addSink(consoleSink)
    .build("Engine");

logger->debug("Debug message");
logger->info("Engine started");
logger->error("Something failed");
```

## Log Levels

ArLogger provides six log levels:

```text
Trace
Debug
Info
Warning
Error
Critical
```

The logger only processes messages at or above its configured level.

```cpp
logger.setLevel(arlogger::LogLevel::Warning);
```

With this configuration:

```text
Trace     ignored
Debug     ignored
Info      ignored
Warning   logged
Error     logged
Critical  logged
```

## Custom Formatting

ArLogger supports customizable formatting patterns.

```cpp
auto formatter =
    std::make_shared<arlogger::DefaultFormatter>(
        "[%date] [%time] [%level] [%logger] [%message] (%file:%line)"
    );
```

### Available Patterns

| Pattern     | Description        |
| ----------- | ------------------ |
| `%date`     | Current local date |
| `%time`     | Current local time |
| `%level`    | Log level          |
| `%logger`   | Logger name        |
| `%message`  | Log message        |
| `%file`     | Source file        |
| `%line`     | Source line        |
| `%function` | Function name      |

Example output:

```text
[2026-09-16] [15:26:20] [INFO] [Engine] [Engine started] (Test.cpp:33)
```

## Logger Hierarchy

Loggers can have parent-child relationships.

```cpp
auto engineLogger =
    std::make_shared<arlogger::Logger>("Engine");

auto rendererLogger =
    std::make_shared<arlogger::Logger>(
        "Engine.Renderer",
        engineLogger
    );

rendererLogger->info("Renderer initialized");
```

A message logged by the child can propagate to its parent:

```text
[INFO] [Engine.Renderer] [Renderer initialized]
[INFO] [Engine] [Renderer initialized]
```

Each logger can have its own log level.

## File Logging

ArLogger provides a `FileSink` for writing logs to a file.

```cpp
auto fileSink =
    std::make_shared<arlogger::FileSink>(
        "engine.log",
        formatter,
        10 * 1024 * 1024
    );
```

The third parameter specifies the maximum file size in bytes.

When the file reaches the configured limit, it is rotated without deleting existing log files:

```text
engine.log
engine.log.1
engine.log.2
engine.log.3
```

Existing rotated files are preserved.

## Source Location

Logging functions automatically capture the source location using `std::source_location`.

```cpp
logger.info("Renderer initialized");
```

A formatter can access:

* Source file
* Line number
* Function name

For example:

```text
(Renderer.cpp:42)
```

## Thread Safety

ArLogger uses C++ synchronization primitives to protect logger state and sink operations, allowing the logger to be used from multiple threads.

## Project Structure

```text
ArLogger/
├── include/
│   └── arlogger/
│       ├── Logger.h
│       ├── LoggerBuilder.h
│       ├── LogLevel.h
│       ├── LogRecord.h
│       ├── Sink.h
│       ├── ConsoleSink.h
│       ├── FileSink.h
│       ├── Formatter.h
│       └── DefaultFormatter.h
│
├── src/
│   ├── Logger.cpp
│   ├── LoggerBuilder.cpp
│   ├── LogLevel.cpp
│   ├── Sink.cpp
│   ├── ConsoleSink.cpp
│   ├── FileSink.cpp
│   └── DefaultFormatter.cpp
│
├── ArLogger.vcxproj
├── ArLogger.slnx
└── LICENSE.txt
```

## License

ArLogger is licensed under the MIT License.

See [LICENSE.txt](LICENSE.txt) for the full license text.
