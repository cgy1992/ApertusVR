#MIT License
#
#Copyright (c) 2018 MTA SZTAKI
#
#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.

# assimp patch log begin
# In /3rdParty/assimp/code/X3DImporter.cpp std::transforms are commented out because of operator != problem
# assimp patch log begin

set (ASSIMP_HOME ${CMAKE_SOURCE_DIR}/3rdParty/assimp)
set (ASSIMP_READY FALSE)


if (WIN32 OR APPLE)

	set(ASSIMP_OUTPUT_FILE_NAME "assimp-vc140-mt")
	set(ASSIMP_OUTPUT_FILE_NAME_STATIC "${ASSIMP_OUTPUT_FILE_NAME}${APE_FILE_EXT_STATIC}")
	set(ASSIMP_OUTPUT_FILE_NAME_SHARED "${ASSIMP_OUTPUT_FILE_NAME}${APE_FILE_EXT_SHARED}")

	# static
	set(ASSIMP_STATIC_LIB_PATH_DEBUG "${ASSIMP_HOME}/lib/Debug/${ASSIMP_OUTPUT_FILE_NAME_STATIC}")
	set(ASSIMP_STATIC_LIB_PATH_RELEASE "${ASSIMP_HOME}/lib/Release/${ASSIMP_OUTPUT_FILE_NAME_STATIC}")

	# shared
	set(ASSIMP_SHARED_LIB_PATH_DEBUG "${ASSIMP_HOME}/bin/Debug/${ASSIMP_OUTPUT_FILE_NAME_SHARED}")
	set(ASSIMP_SHARED_LIB_PATH_RELEASE "${ASSIMP_HOME}/bin/Release/${ASSIMP_OUTPUT_FILE_NAME_SHARED}")

	# output for shared
	set(ASSIMP_SHARED_LIB_PATH_APE_DEBUG "${APE_OUTPUT_DIR_DEBUG}/${ASSIMP_OUTPUT_FILE_NAME_SHARED}")
	set(ASSIMP_SHARED_LIB_PATH_APE_RELEASE "${APE_OUTPUT_DIR_RELEASE}/${ASSIMP_OUTPUT_FILE_NAME_SHARED}")

elseif (APPLE)

	set(ASSIMP_OUTPUT_FILE_NAME "libassimp")
	set(ASSIMP_OUTPUT_FILE_NAME_STATIC "${ASSIMP_OUTPUT_FILE_NAME}${APE_FILE_EXT_STATIC}")
	set(ASSIMP_OUTPUT_FILE_NAME_SHARED "${ASSIMP_OUTPUT_FILE_NAME}${APE_FILE_EXT_SHARED}")

	# static
	set(ASSIMP_STATIC_LIB_PATH_DEBUG "${ASSIMP_HOME}/lib/Debug/${ASSIMP_OUTPUT_FILE_NAME_STATIC}")
	set(ASSIMP_STATIC_LIB_PATH_RELEASE "${ASSIMP_HOME}/lib/Release/${ASSIMP_OUTPUT_FILE_NAME_STATIC}")

	# shared
	set(ASSIMP_SHARED_LIB_PATH_DEBUG "${ASSIMP_HOME}/bin/Debug/${ASSIMP_OUTPUT_FILE_NAME_SHARED}")
	set(ASSIMP_SHARED_LIB_PATH_RELEASE "${ASSIMP_HOME}/bin/Release/${ASSIMP_OUTPUT_FILE_NAME_SHARED}")

	# output for shared
	set(ASSIMP_SHARED_LIB_PATH_APE_DEBUG "${APE_OUTPUT_DIR_DEBUG}/${ASSIMP_OUTPUT_FILE_NAME_SHARED}")
	set(ASSIMP_SHARED_LIB_PATH_APE_RELEASE "${APE_OUTPUT_DIR_RELEASE}/${ASSIMP_OUTPUT_FILE_NAME_SHARED}")

elseif (LINUX)

	set(ASSIMP_OUTPUT_FILE_NAME "libassimp")
	set(ASSIMP_OUTPUT_FILE_NAME_STATIC "${ASSIMP_OUTPUT_FILE_NAME}${APE_FILE_EXT_STATIC}")
	set(ASSIMP_OUTPUT_FILE_NAME_SHARED "${ASSIMP_OUTPUT_FILE_NAME}${APE_FILE_EXT_SHARED}")

	# static
	set(ASSIMP_STATIC_LIB_PATH_RELEASE "${ASSIMP_HOME}/lib/${ASSIMP_OUTPUT_FILE_NAME_STATIC}")

	# shared
	set(ASSIMP_SHARED_LIB_PATH_RELEASE "${ASSIMP_HOME}/lib/${ASSIMP_OUTPUT_FILE_NAME_SHARED}")

	# output for shared
	set(ASSIMP_SHARED_LIB_PATH_APE_RELEASE "${APE_OUTPUT_DIR}/${ASSIMP_OUTPUT_FILE_NAME_SHARED}")

endif ()


#error function
function (reportError what and when)
	if (${${when}})
		message (${${what}})
	endif ()
endfunction ()

#find assimp
message(STATUS "ASSIMP_STATIC_LIB_PATH_RELEASE: ${ASSIMP_STATIC_LIB_PATH_RELEASE}")
if(EXISTS ${ASSIMP_STATIC_LIB_PATH_RELEASE})
	set(ASSIMP_READY TRUE)
	message (STATUS "assimp is installed" )
else ()
	set(ASSIMP_READY FALSE)
	message (STATUS "assimp is not installed" )
endif ()
if (NOT ASSIMP_READY)
#build assimp
	foreach (CONF ${CMAKE_CONFIGURATION_TYPES})
		message (STATUS "Configuring assimp for ${CONF}, please wait.....")
		execute_process ( 
				COMMAND ${CMAKE_COMMAND} 
				-G ${CMAKE_GENERATOR} 
				-DBUILD_SHARED_LIBS=OFF
				-DASSIMP_BUILD_TESTS=OFF
				.
				WORKING_DIRECTORY ${ASSIMP_HOME}
				RESULT_VARIABLE error OUTPUT_VARIABLE output ERROR_VARIABLE output
				)		
		reportError (output if error)
		message (STATUS "Building assimp for ${CONF}, please wait.....")
		execute_process ( 
			COMMAND ${CMAKE_COMMAND} --build . --config ${CONF}
			WORKING_DIRECTORY ${ASSIMP_HOME}
			RESULT_VARIABLE error OUTPUT_VARIABLE output ERROR_VARIABLE output)
		reportError (output if error)
	endforeach ()
endif ()
#use assimp
add_library(MY_ASSIMP STATIC IMPORTED)
set_property(TARGET MY_ASSIMP PROPERTY IMPORTED_LOCATION_DEBUG ${ASSIMP_STATIC_LIB_PATH_DEBUG})
set_property(TARGET MY_ASSIMP PROPERTY IMPORTED_LOCATION_RELEASE ${ASSIMP_STATIC_LIB_PATH_RELEASE})

#ApeAssimpAssetLoaderPlugin
set (HEADERS
	ApeAssimpAssetLoaderPlugin.h
	)

set (SOURCES 
	ApeAssimpAssetLoaderPlugin.cpp
	)

include_directories(
	${PROJECT_SOURCE_DIR}/common/include  
	${ASSIMP_HOME}/include
	${RAPIDJSON_INCLUDE_DIR}
	)

# Add the dinamic library target to the project
add_library (ApeAssimpAssetLoaderPlugin SHARED ${SOURCES} ${HEADERS})

# Link with dependency libraries
set_property (TARGET ApeAssimpAssetLoaderPlugin PROPERTY COMPILE_DEFINITIONS APE_BIN_DIR="${APE_BIN_DIR}" APE_SOURCE_DIR="${APE_SOURCE_DIR}")

if (LINUX)
	target_link_libraries (ApeAssimpAssetLoaderPlugin ApePluginManager ApeSceneManager ApeEventManager ApeLogManager ApeSystemConfig ApeMainWindow ${ASSIMP_STATIC_LIB_PATH_RELEASE})
else ()
	target_link_libraries (ApeAssimpAssetLoaderPlugin ApePluginManager ApeSceneManager ApeEventManager ApeLogManager ApeSystemConfig ApeMainWindow MY_ASSIMP)
endif ()

# Place target xxx into the specified folder in IDEs supporting it
set_property (TARGET ApeAssimpAssetLoaderPlugin PROPERTY FOLDER "Plugins")

foreach (CONF ${CMAKE_CONFIGURATION_TYPES})
	if(NOT EXISTS ${ASSIMP_SHARED_LIB_PATH_APE_${CONF}})
		file(COPY ${ASSIMP_SHARED_LIB_PATH_${CONF}} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CONF})
	endif()
endforeach ()

# debug dlls
# if(NOT EXISTS ${ASSIMP_SHARED_LIB_PATH_APE_DEBUG})
# 	file(COPY ${ASSIMP_SHARED_LIB_PATH_DEBUG} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug)
# endif()
# release dlls
# if(NOT EXISTS ${ASSIMP_SHARED_LIB_PATH_APE_RELEASE})
# 	file(COPY ${ASSIMP_SHARED_LIB_PATH_RELEASE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release)
# endif()
