cmake_minimum_required(VERSION 3.20)

project(ArLogger
    VERSION 1.0.0
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(ArLogger STATIC
    src/Logger.cpp
    src/LoggerBuilder.cpp
    src/LogLevel.cpp
    src/Sink.cpp
    src/ConsoleSink.cpp
    src/FileSink.cpp
    src/DefaultFormatter.cpp
)

target_include_directories(ArLogger
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(ArLogger
    PUBLIC
        cxx_std_20
)

configure_package_config_file(
    cmake/ArLoggerConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ArLoggerConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ArLogger
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ArLoggerConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    TARGETS ArLogger
    EXPORT ArLoggerTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/$<CONFIG>
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/$<CONFIG>
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/$<CONFIG>
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT ArLoggerTargets
    FILE ArLoggerTargets.cmake
    NAMESPACE ArLogger::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ArLogger
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/ArLoggerConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/ArLoggerConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ArLogger
)