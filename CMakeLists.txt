if (WIN32)
    cmake_minimum_required(VERSION 3.18)
else()
    cmake_minimum_required(VERSION 3.14)
endif()

if (APPLE)
  if (CMAKE_CXX_COMPILER MATCHES "clang")
    message(WARNING "You may need to configure linker version when using Clang or AppleClang.")
    set(CMAKE_CXX_FLAGS "-mlinker-version=450")
    set(CMAKE_C_FLAGS "-mlinker-version=450")
  endif()
endif()

project(msclient)

# Set project options
include(cmake/StandardSettings.cmake)
include(cmake/Utils.cmake)
include(cmake/Doxygen.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/StaticAnalyzers.cmake)
include(thirdparty/Deps.cmake)
include(GNUInstallDirs)
if (UNIX)
    include(FindFreetype)
endif()

add_subdirectory(src)