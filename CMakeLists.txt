
cmake_minimum_required(VERSION 3.16)

set(STM32_DEVICE "STM32F746xx")
set(MCU_LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/F7/Cube/STM32F746VGTx_FLASH.ld")

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/F7/cmake/stm32_gcc.cmake)

#set(LFRAMEWORK_CONFIG_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

project(sandbox CXX C ASM)


#stm32_fetch_cmsis()

set(PROJECT_NAME "sandbox")
add_executable(${PROJECT_NAME} )

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_compile_definitions(${PROJECT_NAME} PRIVATE ${STM32_DEVICE})


add_subdirectory(F7)
add_subdirectory(Dependencies/LFramework)
add_subdirectory(Dependencies/MicroNetworkCommon)
add_subdirectory(Dependencies/MicroNetworkDevice)

target_link_libraries(MicroNetworkDevice INTERFACE MicroNetworkCommon)
target_link_libraries(${PROJECT_NAME} MicroNetworkCommon)
target_link_libraries(${PROJECT_NAME} MicroNetworkDevice)




