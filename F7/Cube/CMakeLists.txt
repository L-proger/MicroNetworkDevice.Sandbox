add_library(Cube STATIC)
set_property(TARGET Cube PROPERTY CXX_STANDARD 17)

add_subdirectory(Src)
add_subdirectory(startup)

target_include_directories(Cube PUBLIC Inc)
target_include_directories(Cube PUBLIC Drivers/CMSIS/Device/ST/STM32F7xx/Include)
target_include_directories(Cube PUBLIC Middlewares/ST/STM32_USB_Device_Library_/Core/Inc)
target_include_directories(Cube PUBLIC Middlewares/Third_Party/FreeRTOS/Source/include)
target_include_directories(Cube PUBLIC Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1)