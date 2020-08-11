cmake_minimum_required(VERSION 3.10)

project(GossipMembershipProtocol)

set(EXEC application)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories(includes/)

file(GLOB SOURCES src/*.cpp)

add_executable(${EXEC} ${SOURCES})