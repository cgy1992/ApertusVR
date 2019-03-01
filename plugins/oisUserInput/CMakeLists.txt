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

# ois patch log begin
# CMakeLists.txt was copied to the ois root folder
# Win32KeyBoard.h ln 54 was edited { return KeyCode::KC_UNASSIGNED;/*TODO: Implement OS version*/; }
# ois patch log begin

include("cmake/prepare_ois.cmake")

set (HEADERS
	ApeOisUserInputPlugin.h
	ApeOisUserInputPluginConfigs.h
	)

set (SOURCES 
	ApeOisUserInputPlugin.cpp
	)

include_directories(
	${PROJECT_SOURCE_DIR}/common/include  
	${OIS_INCLUDE_DIRS}
	${RAPIDJSON_INCLUDE_DIR}
	)

# Add the dinamic library target to the project
add_library (ApeOisUserInputPlugin SHARED ${SOURCES} ${HEADERS})

# Link with dependency libraries
if (LINUX)
	target_link_libraries (ApeOisUserInputPlugin ApePluginManager ApeSceneManager ApeEventManager ApeLogManager ApeSystemConfig ApeMainWindow ${OIS_STATIC_LIB_PATH_RELEASE})	
else ()
	target_link_libraries (ApeOisUserInputPlugin ApePluginManager ApeSceneManager ApeEventManager ApeLogManager ApeSystemConfig ApeMainWindow MY_OIS)
endif ()

if (WIN32)
	# we have to link to some DirectX libraries 
	target_link_libraries (ApeOisUserInputPlugin dinput8 dxguid)
endif ()

# Place target xxx into the specified folder in IDEs supporting it
set_property (TARGET ApeOisUserInputPlugin PROPERTY FOLDER "Plugins")
