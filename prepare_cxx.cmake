# on Apple we need to use C++11
if (APPLE)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_VERBOSE_MAKEFILE on )
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	add_definitions(-std=c++11)
endif ()

if (UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif ()
