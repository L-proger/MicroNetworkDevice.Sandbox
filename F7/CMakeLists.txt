target_sources(ArzhanovF7Devboard
PRIVATE 
	LFrameworkConfig.h
	main.cpp 
	rtos.c
	Tasks/ReadMemoryTask.h
	Usb/Usb.h
	Usb/Usb.cpp
)

add_subdirectory(Cube)


target_include_directories(ArzhanovF7Devboard PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ArzhanovF7Devboard PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces)


