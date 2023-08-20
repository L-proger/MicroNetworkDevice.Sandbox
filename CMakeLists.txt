
cmake_minimum_required(VERSION 3.16)


set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/LFramework.CMake/stm32_gcc.cmake)

#set(LFRAMEWORK_CONFIG_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

project(sandbox CXX C ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/LFramework.CMake/stm32)
set(STM32_DEVICE STM32F746VGT6)

include(fetch)
FetchStm32Hal()
FetchStm32FreeRtos()
FetchStm32CmsisDevice()
FetchStm32CmsisCore()
FetchStm32UsbDevice()

find_package(Stm32Hal REQUIRED)
find_package(Stm32FreeRtos REQUIRED)
find_package(Stm32CmsisDevice REQUIRED)
find_package(Stm32CmsisCore REQUIRED)
find_package(Stm32UsbDevice REQUIRED)


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
    Stm32Hal
    Stm32FreeRtos
    Stm32CmsisDevice
    Stm32CmsisCore
    Stm32UsbDevice
    LFramework
    LFramework::Usb
    LFramework::Usb::Device
    LFramework::UnitTest
    MicroNetworkCommon 
    MicroNetworkDevice
    STM32::F7
    GCC::Specs::NoSys
    GCC::Specs::Nano
)

gcc_add_linker_script( ArzhanovF7Devboard PRIVATE "${CMAKE_CURRENT_LIST_DIR}/F7/Cube/STM32F746VGTx_FLASH.ld" )
gcc_print_target_size( ArzhanovF7Devboard )




