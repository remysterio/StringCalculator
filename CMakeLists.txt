cmake_minimum_required(VERSION 3.5)

project(Calculator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_executable(Calculator
  main.cpp
  StringSimple.cpp
  StringSimple.h
  Verification.cpp
  Verification.h
  StringComplex.cpp
  StringComplex.h
)
target_link_libraries(Calculator Qt5::Core)
