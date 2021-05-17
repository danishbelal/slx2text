# Add ZipLib Target
#
# The original library does not provide proper build scripts :(
#
# This might need further tuning to seamlessly work on all platforms.
set(ZIPLIB_DIR "${CMAKE_SOURCE_DIR}/external/ziplib/Source/ZipLib")
set(ZIPLIB_SOURCES "")

file(GLOB ZipLibFiles "${ZIPLIB_DIR}/*.[hc]*")
list(APPEND ZIPLIB_SOURCES "${ZipLibFiles}")

file(GLOB ZipLibFiles "${ZIPLIB_DIR}/detail/*.[hc]*")
list(APPEND ZIPLIB_SOURCES "${ZipLibFiles}")

file(GLOB ZipLibFiles "${ZIPLIB_DIR}/extlibs/bzip2/*.[hc]*")
list(APPEND ZIPLIB_SOURCES "${ZipLibFiles}")

file(GLOB ZipLibFiles "${ZIPLIB_DIR}/compression/bzip2/*.[hc]*")
list(APPEND ZIPLIB_SOURCES "${ZipLibFiles}")

# ZLIB is linked independently down below.
#file(GLOB ZipLibFiles "${ZIPLIB_DIR}/extlibs/zlib/*.[hc]*")
#list(APPEND ZIPLIB_SOURCES "${ZipLibFiles}")

# Unix specific
# TODO: Add os specific switch case
file(GLOB ZipLibFiles "${ZIPLIB_DIR}/extlibs/lzma/unix/*.[hc]")
list(APPEND ZIPLIB_SOURCES "${ZipLibFiles}")

set(ZipLibIncludes "${ZIPLIB_DIR}"
                   "${ZIPLIB_DIR}/detail"
                   "${ZIPLIB_DIR}/extlibs/lzma/unis")

add_library(ZipLib "${ZIPLIB_SOURCES}")
target_include_directories(ZipLib PUBLIC "${ZipLibIncludes}")

find_package(ZLIB REQUIRED)
target_link_libraries(ZipLib PUBLIC ZLIB::ZLIB)