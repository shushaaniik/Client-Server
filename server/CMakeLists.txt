cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 14)

project(server)

include_directories(../include)

add_executable(server
  ../src/prime_nums.cpp
  ../src/socket.cpp
  ../src/talker.cpp
  ../src/thread_pool.cpp
  server.cpp
)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}")
