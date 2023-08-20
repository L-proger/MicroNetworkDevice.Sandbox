
cmake_minimum_required(VERSION 3.16)

set(STM32_DEVICE "STM32F746xx")

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/LFramework.CMake/stm32_gcc.cmake)

#set(LFRAMEWORK_CONFIG_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

project(sandbox CXX C ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

#stm32_fetch_cmsis()

set(PROJECT_NAME "sandbox")
add_executable(ArzhanovF7Devboard )

target_compile_definitions(ArzhanovF7Devboard 
PRIVATE 
    STM32F746xx
)


add_subdirectory(F7)
add_subdirectory(Dependencies/LFramework)
add_subdirectory(Dependencies/MicroNetworkCommon)
add_subdirectory(Dependencies/MicroNetworkDevice)

target_link_libraries(ArzhanovF7Devboard 
PRIVATE
    LFramework 
    MicroNetworkCommon 
    MicroNetworkDevice
    STM32::F7
    GCC::Specs::NoSys
    GCC::Specs::Nano
)

gcc_add_linker_script( ArzhanovF7Devboard PRIVATE "${CMAKE_CURRENT_LIST_DIR}/F7/Cube/STM32F746VGTx_FLASH.ld" )
gcc_print_target_size( ArzhanovF7Devboard )




