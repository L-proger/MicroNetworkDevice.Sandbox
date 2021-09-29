
cmake_minimum_required(VERSION 3.16)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32_gcc.cmake)



#set(LFRAMEWORK_CONFIG_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

project(sandbox CXX C ASM)
set(STM32_DEVICE "STM32F746xx")
#stm32_fetch_cmsis()

set(PROJECT_NAME "sandbox")
add_executable(${PROJECT_NAME} )

target_sources(${PROJECT_NAME} 
	PUBLIC
		LFrameworkConfig.h
	PRIVATE 
		main.cpp 
		rtos.c
)

target_compile_definitions(${PROJECT_NAME} PRIVATE ${STM32_DEVICE})

target_compile_definitions(${PROJECT_NAME} PUBLIC "-D__weak=__attribute__((weak))" "-D__packed=__attribute__((__packed__))")


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces)

add_subdirectory(Cube)
add_subdirectory(Tasks)
add_subdirectory(Usb)

add_subdirectory(../Dependencies/LFramework LFramework)
add_subdirectory(../Dependencies/MicroNetworkCommon MicroNetworkCommon)
add_subdirectory(../Dependencies/MicroNetworkDevice MicroNetworkDevice)

target_link_libraries(MicroNetworkDevice INTERFACE MicroNetworkCommon)
target_link_libraries(${PROJECT_NAME} MicroNetworkCommon)
target_link_libraries(${PROJECT_NAME} MicroNetworkDevice)




