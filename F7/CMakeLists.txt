
cmake_minimum_required(VERSION 3.16)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32_gcc.cmake)

project(sandbox CXX C ASM)

add_executable(sandbox main.cpp)

target_compile_definitions(sandbox PRIVATE STM32F746xx)

add_subdirectory(Cube)