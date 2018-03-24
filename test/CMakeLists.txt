project(cpumem_monitortest)

if(WIN32) 
	set(CPUMONITOR_PLATFORM_LIBS 
		pdh
	)
else() 
	find_package(Threads REQUIRED)
	set(CPUMONITOR_PLATFORM_LIBS 
		${CMAKE_THREAD_LIBS_INIT}
	)
endif()
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} cpumem_monitor ${CPUMONITOR_PLATFORM_LIBS})
add_test (NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
