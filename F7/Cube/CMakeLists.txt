#add_library(Cube STATIC)
#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)


file(GLOB_RECURSE CUBE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/**/*.h")
file(GLOB_RECURSE CUBE_C_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/**/*.c")
file(GLOB_RECURSE CUBE_ASM_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/**/*.S")

list(FILTER CUBE_C_SOURCES EXCLUDE REGEX ".*syscalls.c$")

target_sources(${PROJECT_NAME} PUBLIC ${CUBE_HEADERS} PRIVATE ${CUBE_C_SOURCES} ${CUBE_ASM_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${STM32_DEVICE})


target_include_directories(${PROJECT_NAME} PRIVATE ${USB_DEVICE_INC_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC Inc)
target_include_directories(${PROJECT_NAME} PUBLIC Drivers/STM32F7xx_HAL_Driver/Inc)
target_include_directories(${PROJECT_NAME} PUBLIC Drivers/CMSIS/Device/ST/STM32F7xx/Include)
target_include_directories(${PROJECT_NAME} PUBLIC Drivers/CMSIS/Include)
target_include_directories(${PROJECT_NAME} PUBLIC Middlewares/ST/STM32_USB_Device_Library_/Core/Inc)
target_include_directories(${PROJECT_NAME} PUBLIC Middlewares/Third_Party/FreeRTOS/Source/include)
target_include_directories(${PROJECT_NAME} PUBLIC Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS)
target_include_directories(${PROJECT_NAME} PUBLIC Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1)
