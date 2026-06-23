cmake_minimum_required(VERSION 3.16)

project(order_matching_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    order_matching_engine
    src/main.cpp
)

target_include_directories(
    order_matching_engine
    PRIVATE
    include
)
