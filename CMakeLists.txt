cmake_minimum_required(VERSION 3.15)
project(Homeworks C ASM)

if(MSVC)
	add_compile_options(/W4 /WX)	
else()
	add_compile_options(-Wall -Wextra -Wpedantic)	
endif()

include(CTest)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(stdhw)
add_subdirectory(hws)

