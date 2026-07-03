cmake_minimum_required(VERSION 3.28)

project(OrderMatchingEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable optimations for release builds
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_compile_options("-Wall" "-Wextra" "-pedantic")

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

# Include directories
include_directories(include)

# Add core source file libraries
add_library(core STATIC ${SOURCES})

target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)
