cmake_minimum_required(VERSION 3.10)
project(miniProject1)

set(CMAKE_CXX_STANDARD 11)

# src 및 하위 디렉토리 포함
include_directories(src)

# src 디렉토리 내 모든 cpp 파일을 소스에 추가
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(miniProject1 ${SOURCES})