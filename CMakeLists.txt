cmake_minimum_required(VERSION 3.16)
project(slx2text LANGUAGES C CXX) # C is only used for ZipLib

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# External Dependencies: pugixml, ZipLib and threads
add_subdirectory(external/pugixml)
find_package(Threads REQUIRED)
include(ZipLibTarget)

# Main Program
add_subdirectory(source)
