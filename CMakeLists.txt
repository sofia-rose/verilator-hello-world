cmake_minimum_required(VERSION 3.12)

project(verilator-hello-world)

find_package(verilator)
if (NOT verilator_FOUND)
  message(FATAL_ERROR "Verilator was not found!")
endif()

add_executable(hello ./test/sim_main.cpp)

verilate(
  hello
  COVERAGE
  TRACE
  VERILATOR_ARGS -Wall
  SOURCES src/full_adder.v
)
