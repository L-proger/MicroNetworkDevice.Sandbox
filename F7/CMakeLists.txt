target_sources(ArzhanovF7Devboard
	PUBLIC
		LFrameworkConfig.h
	PRIVATE 
		main.cpp 
		rtos.c
)

add_subdirectory(Cube)
add_subdirectory(Tasks)
add_subdirectory(Usb)


target_include_directories(ArzhanovF7Devboard PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ArzhanovF7Devboard PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces)


