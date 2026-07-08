cmake_minimum_required(VERSION 3.28)

project(OrderMatchingEngine LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings and optimizations
add_compile_options(-Wall -Wextra -pedantic)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SOURCES 
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Create executable
add_executable(OrderMatchingEngine ${SOURCES})

set_target_properties(OrderMatchingEngine PROPERTIES 
    OUTPUT_NAME "order_matching_engine"
)