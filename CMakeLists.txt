cmake_minimum_required(VERSION 3.16)
project(slx2text LANGUAGES C CXX) # C is only used for ZipLib

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

# External Dependencies: pugixml, tomlplusplus, ZipLib and threads
add_subdirectory(external/pugixml)
add_subdirectory(external/tomlplusplus)
find_package(Threads REQUIRED)
include(ZipLibTarget)

# Main Program
add_subdirectory(source)
