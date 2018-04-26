cmake_minimum_required(VERSION 3.7)
project(mc833)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c data_structures.c protocol_messages.h server.c server.h protocol.c protocol.h)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(mc833 ${SOURCE_FILES})