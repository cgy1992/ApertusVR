# set platform variables
if (APPLE OR UNIX)
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif ()
if (UNIX AND NOT APPLE)
	set(LINUX TRUE)
	if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
		set(LINUX_X64 TRUE)
	endif ()
endif ()

# require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions(-std=c++11)

# set compiler to g++ on Linux
if (LINUX)
	set(CMAKE_CXX_COMPILER "/usr/bin/c++")

	if (LINUX_X64)
		message(STATUS "Add -fPIC to CMAKE_CXX_FLAGS for Linux X64 build")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -D_GLIBCXX_USE_CXX11_ABI=0")
		add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
		set(CMAKE_POSITION_INDEPENDENT_CODE ON)
	endif ()
endif ()
