if (LINUX)
    set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "Semicolon separated list" FORCE)
elseif (APPLE OR WIN32)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Semicolon separated list" FORCE)
endif ()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# use solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
