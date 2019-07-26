

set(command "C:/Program Files/CMake/bin/cmake.exe;-Dmake=${make};-Dconfig=${config};-P;C:/ApertusVR/3rdParty/ogre21/ogre/Dependencies/src/SDL2-prefix/src/SDL2-stamp/SDL2-MoveInstallFiles-Debug-impl.cmake")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "C:/ApertusVR/3rdParty/ogre21/ogre/Dependencies/src/SDL2-prefix/src/SDL2-stamp/SDL2-MoveInstallFiles-out.log"
  ERROR_FILE "C:/ApertusVR/3rdParty/ogre21/ogre/Dependencies/src/SDL2-prefix/src/SDL2-stamp/SDL2-MoveInstallFiles-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  C:/ApertusVR/3rdParty/ogre21/ogre/Dependencies/src/SDL2-prefix/src/SDL2-stamp/SDL2-MoveInstallFiles-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "SDL2 MoveInstallFiles command succeeded.  See also C:/ApertusVR/3rdParty/ogre21/ogre/Dependencies/src/SDL2-prefix/src/SDL2-stamp/SDL2-MoveInstallFiles-*.log")
  message(STATUS "${msg}")
endif()
