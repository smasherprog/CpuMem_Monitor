cmake_minimum_required(VERSION 3.8)
project(cpumem_monitor)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(BUILD_EXAMPLE "Build example" ON)
option(BUILD_SHARED_LIBS "Build shared library" OFF) 

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

add_library(${PROJECT_NAME} cpumem_monitor.h cpumem_monitor.cpp)

install (TARGETS ${PROJECT_NAME}  
	RUNTIME DESTINATION bin
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
)

install (FILES 
	cpumem_monitor.h 
	DESTINATION include
)

if(BUILD_EXAMPLE)
  add_subdirectory(Test)
endif()

