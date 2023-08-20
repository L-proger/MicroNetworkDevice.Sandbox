target_sources(ArzhanovF7Devboard
PRIVATE 
	LFrameworkConfig.h
	main.cpp 
	rtos.c
	Tasks/MemoryAccess.h
	Usb/Usb.h
	Usb/Usb.cpp
)


target_include_directories(ArzhanovF7Devboard PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ArzhanovF7Devboard PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces)


