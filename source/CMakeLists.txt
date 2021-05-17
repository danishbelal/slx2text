# Main Program

set(DemoSources "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/DumpAllFiles.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/ZipFileIterator.hpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/ZipFileIterator.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/playground.cpp")

add_executable(Demo "${DemoSources}")
target_link_libraries(Demo PUBLIC ZipLib pugixml::pugixml Threads::Threads)