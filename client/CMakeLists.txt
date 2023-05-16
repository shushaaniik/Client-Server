cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 14)

project(client)

include_directories(../include)

add_executable(client
  ../src/socket.cpp
  client.cpp
)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}")
