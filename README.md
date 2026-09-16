
# ArLogger

A lightweight and extensible C++ logging library for Windows.

ArLogger provides hierarchical loggers, customizable formatting, console and file sinks, multiple log levels, source location tracking, thread safety, and automatic log file rotation.

## Features

- Windows support
- C++20
- Six log levels: Trace, Debug, Info, Warning, Error, and Critical
- Hierarchical parent-child loggers
- Console and file sinks
- Customizable log formatting
- Source location tracking with `std::source_location`
- Thread-safe logging
- Log level filtering
- Configurable automatic flushing
- Log file size limits
- Non-destructive log rotation
- Fluent `LoggerBuilder` API
- CMake package support

## Requirements

- Windows
- Visual Studio 2022
- C++20 or newer
- CMake 3.20 or newer

## Installation

### Using CMake FetchContent

Add ArLogger directly from GitHub using CMake.

```cmake
include(FetchContent)

FetchContent_Declare(
    ArLogger
    GIT_REPOSITORY https://github.com/ar40ae/ArLogger.git
    GIT_TAG v1.0.0
)

FetchContent_MakeAvailable(ArLogger)

add_executable(MyApplication
    main.cpp
)

target_link_libraries(MyApplication
    PRIVATE
        ArLogger
)
```

### Using an Installed CMake Package

ArLogger can also be installed and used as a CMake package.

```cmake
find_package(ArLogger CONFIG REQUIRED)

add_executable(MyApplication
    main.cpp
)

target_link_libraries(MyApplication
    PRIVATE
        ArLogger::ArLogger
)
```

Specify the installation directory when configuring your project:

```powershell
cmake -S . -B build `
    -DCMAKE_PREFIX_PATH="D:/C++/ArLogger/install"
```

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

    return 0;
}
```

## LoggerBuilder

`LoggerBuilder` provides a fluent API for configuring and creating loggers.

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

| Level | Description |
|-------|-------------|
| Trace | Detailed diagnostic information |
| Debug | Development and debugging information |
| Info | General application information |
| Warning | Potential problems |
| Error | Errors that require attention |
| Critical | Serious application failures |

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

| Pattern | Description |
|---------|-------------|
| `%date` | Current local date |
| `%time` | Current local time |
| `%level` | Log level |
| `%logger` | Logger name |
| `%message` | Log message |
| `%file` | Source file |
| `%line` | Source line |
| `%function` | Function name |

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

Child loggers can propagate messages to their parent logger.

Each logger can have its own log level and configuration.

## File Logging

ArLogger provides a `FileSink` for writing logs to files.

```cpp
auto fileSink =
    std::make_shared<arlogger::FileSink>(
        "engine.log",
        formatter,
        10 * 1024 * 1024
    );
```

The third parameter specifies the maximum file size in bytes.

When the file reaches the configured limit, it is rotated without deleting existing log files.

```text
engine.log
engine.log.1
engine.log.2
engine.log.3
```

Existing rotated files are preserved.

## Source Location

Logging functions automatically capture source location information using `std::source_location`.

```cpp
logger.info("Renderer initialized");
```

A formatter can access:

- Source file
- Line number
- Function name

Example:

```text
(Renderer.cpp:42)
```

## Thread Safety

ArLogger uses C++ synchronization primitives to protect logger state and sink operations, allowing loggers to be used from multiple threads.

## Building from Source

Clone the repository:

```powershell
git clone https://github.com/ar40ae/ArLogger.git
cd ArLogger
```

Configure and build the project:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

To build the Debug configuration:

```powershell
cmake --build build --config Debug
```

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
├── cmake/
│   └── ArLoggerConfig.cmake.in
│
├── CMakeLists.txt
├── LICENSE.txt
└── README.md
```

## Repository

[GitHub Repository](https://github.com/ar40ae/ArLogger)

## License

ArLogger is licensed under the MIT License.

See [LICENSE.txt](LICENSE.txt) for the full license text.
