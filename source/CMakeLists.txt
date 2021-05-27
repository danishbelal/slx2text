# Main Program

set(DemoSources "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/ZipFileIterator.hpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/ZipFileIterator.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/ZipUtils.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/ZipUtils.hpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/SlxUtils.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/SlxUtils.hpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/ConfigReader.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/ConfigReader.hpp")

add_executable(Demo "${DemoSources}")
target_link_libraries(Demo PUBLIC ZipLib pugixml::pugixml Threads::Threads tomlplusplus::tomlplusplus)