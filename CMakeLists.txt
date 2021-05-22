cmake_minimum_required(VERSION 3.16)
project(slx2text LANGUAGES C CXX) # C is only used for ZipLib

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(external/pugixml)
find_package(Threads REQUIRED)
include(ZipLibTarget)

# Main Program
add_subdirectory(source)
