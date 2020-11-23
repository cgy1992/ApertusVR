cmake_minimum_required(VERSION 3.18)
project(apeFilamentRenderMacPlugin C CXX OBJC)


set(APP apeFilamentRenderMacPlugin)

set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO")

# Xcode XIB/Storyboard
set(APP_XIB ${CMAKE_CURRENT_SOURCE_DIR}/Base.lproj/MainMenu.xib)

set(LIB_PATH ${CMAKE_SOURCE_DIR}/plugins/render/filamentRenderMac/lib/x86_64/)

find_package (Threads)

set(LIBS filamat filament gltfio backend bluegl bluevk filabridge filaflat utils geometry smol-v ibl)

#add_executable(${APP} MACOSX_BUNDLE
#	main.mm
#	AppDelegate.h
#	AppDelegate.m
#	MainViewController.h
#	MainViewController.mm
#	apeFilamentRenderMacPlugin.h
#	apeFilamentRenderMacPlugin.mm
#	${APP_XIB}
#)

set( HEADERS
	Appdelegate.h
	MainViewController.h
	apeFilamentRenderMacPlugin.h
)

set( SOURCES
    main.mm
	AppDelegate.m
	MainViewController.mm
	apeFilamentRenderMacPlugin.mm
    ${APP_XIB}
)

add_library ( ${APP} SHARED ${SOURCES} ${HEADERS})
set_property (TARGET ${APP} PROPERTY FOLDER "Plugins/Render" PROPERTY COMPILE_DEFINITIONS APE_SOURCE_DIR="${APE_SOURCE_DIR}")
set_property (TARGET ${APP} PROPERTY FOLDER "Plugins/Render")


# Ninja: handle the XIB ourselves
if (NOT ${CMAKE_GENERATOR} MATCHES "^Xcode.*")
	# Compile the xib/storyboard file with the ibtool.
	find_program(IBTOOL NAMES ibtool)

	add_custom_command(TARGET ${APP} POST_BUILD
		COMMAND ${IBTOOL} — errors — warnings — notices — output-format human-readable-text
		— compile 
		${CMAKE_CURRENT_BINARY_DIR}/${APP}.app/Contents/Resources/MainMenu.nib
		${APP_XIB}
		COMMENT "Compiling xib"
	)
endif()
set_target_properties(${APP} PROPERTIES
	MACOSX_BUNDLE YES
	MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
	RESOURCE "${APP_XIB}"
)

foreach(lib ${LIBS})
        add_library(${lib} STATIC IMPORTED)
        set_target_properties(${lib} PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/plugins/render/filamentRenderMac/lib/x86_64/lib${lib}.a)
        target_link_libraries(${APP} ${lib})
endforeach()


target_link_libraries(${APP} apeEventManager apePluginManager apeSceneManager apeCoreConfig  apeSystem "-framework Cocoa -framework Metal -framework CoreVideo")


target_link_libraries(${APP} pthread c++ dl)
target_include_directories(${APP} PUBLIC ./include)
